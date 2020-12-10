#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"

#include <QAbstractItemView>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    windowAdd = new WindowAdd();
    windowEdit = new WindowEdit();

    connect(this->windowAdd,SIGNAL(addNewPressed(Drink&)),&DBParser::getInstance(),SLOT(addDrink(Drink&)));
    connect(this->windowEdit,SIGNAL(editPressed(Drink&)),&DBParser::getInstance(),SLOT(updateDrink(Drink&)));
    connect(&DBParser::getInstance(),SIGNAL(successfulLogin(const User&)),this,SLOT(authorize(const User&)));
    connect(&DBParser::getInstance(),SIGNAL(dataChanged(QList<Drink>*, QList<User>*)),this,SLOT(refresh(QList<Drink>*, QList<User>*)));

    drinkModel = new DrinkModel(this);
    userModel = new UserModel(this);

    ui->mainTable->setModel(drinkModel);
    ui->mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mainTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->mainTable->setColumnWidth(0,150);
    ui->mainTable->setColumnWidth(1,150);
    ui->mainTable->setColumnWidth(2,320);
    ui->mainTable->setColumnWidth(3,100);

    ui->mainTable->horizontalHeader()->setVisible(true);
    ui->mainTable->show();

    ui->pendingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pendingTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pendingTable->setModel(userModel);

    ui->pendingTable->horizontalHeader()->setVisible(true);
    ui->pendingTable->show();


    //refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authorize(const User &user)
{
    this->currentUser=DBParser::getInstance().getUser(user);

    this->show();

    //qDebug()<<this->ui->mainTable->model()->data(ui->mainTable->model()->index(0,0));

    //this->refresh();
    //qDebug("OH YEAH MISTER CRABS");
    qDebug()<<currentUser;
    refresh(DBParser::getInstance().getAllDrinks(),
            DBParser::getInstance().getPendingUsersForId(this->currentUser.id));
}

void MainWindow::refresh(QList<Drink>* drinks, QList<User>* users)
{
    //this->drinkModel->clearAll();
    this->drinkModel->refresh(drinks);
    this->userModel->refresh(users);
}

void MainWindow::on_pushButton_3_clicked()
{
    windowAdd->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    refresh(DBParser::getInstance().getAllDrinks());
}

//Transfering data to windowEdit
void MainWindow::on_pushButton_4_clicked()
{
    int selectedRow = ui->mainTable->selectionModel()->currentIndex().row();
    QString tempName = ui->mainTable->model()->index(selectedRow,0).data().toString();
    drinkType tempType = getDrinkTypeFromString(ui->mainTable->model()->index(selectedRow,1).data().toString());
    QString tempDescription = ui->mainTable->model()->index(selectedRow,2).data().toString();
    //MEGA CRUTCH
    QPixmap photo = this->drinkModel->drinks->operator[](selectedRow).photo;
    int tempId =this->drinkModel->drinks->operator[](selectedRow).id;
    qDebug()<<"TEMP ID : "<<tempId;
    Drink chosenDrink(tempId,tempName,tempDescription,tempType,photo);
    windowEdit->getDrinkData(chosenDrink);
    windowEdit->show();
}

void MainWindow::on_buttonApprove_clicked()
{
    int selectedRow = ui->pendingTable->selectionModel()->currentIndex().row();
    QString username = ui->pendingTable->model()->index(selectedRow,0).data().toString();
    int tempId = this->userModel->users->operator[](selectedRow).id;
    DBParser::getInstance().addApproval({tempId,username,"","",0,""}
                                        ,this->currentUser.id);
}
