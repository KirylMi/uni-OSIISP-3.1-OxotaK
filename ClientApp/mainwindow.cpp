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
    windowMark = new WindowMark();

    connect(this->windowAdd,SIGNAL(addNewPressed(Drink&)),&DBParser::getInstance(),SLOT(addDrink(Drink&)));
    connect(this->windowEdit,SIGNAL(editPressed(Drink&)),&DBParser::getInstance(),SLOT(updateDrink(Drink&)));
    connect(this->windowMark,SIGNAL(markPressed(Drink&,const QString&, const int&, const int&)),
            &DBParser::getInstance(),SLOT(rankDrink(Drink&,const QString&, const int&, const int&)));

    connect(&DBParser::getInstance(),SIGNAL(successfulLogin(const User&)),this,SLOT(authorize(const User&)));
    connect(&DBParser::getInstance(),SIGNAL(dataChanged(QList<Drink>*, QList<User>*)),this,SLOT(refresh(QList<Drink>*, QList<User>*)));
    connect(&DBParser::getInstance(),SIGNAL(dataChanged(QMap<Drink,int>*, QList<User>*)),this,SLOT(refresh(QMap<Drink,int>*, QList<User>*)));
    connect(&DBParser::getInstance(),SIGNAL(dataChanged(QList<User>*)),this,SLOT(refresh(QList<User>*)));

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
    ui->pendingTable->setColumnWidth(0,150);
    ui->pendingTable->setColumnWidth(1,500);

    ui->pendingTable->horizontalHeader()->setVisible(true);
    ui->pendingTable->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authorize(const User &user)
{
    this->currentUser=DBParser::getInstance().getUser(user);

    this->show();

    qDebug()<<currentUser;
    refresh(DBParser::getInstance().getAllDrinksMarks(this->currentUser.id),
            DBParser::getInstance().getPendingUsersForId(this->currentUser.id));
}

void MainWindow::refresh(QMap<Drink, int> *drinksMarks, QList<User> *users)
{
    this->drinkModel->refresh(drinksMarks);
    this->userModel->refresh(users);
}

void MainWindow::refresh(QList<User> *users)
{
    this->userModel->refresh(users);
}

void MainWindow::refresh(QList<Drink>* drinks, QList<User>* users)
{
    this->drinkModel->refresh(drinks);
    this->userModel->refresh(users);
}

void MainWindow::on_pushButton_3_clicked()
{
    windowAdd->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    refresh(DBParser::getInstance().getAllDrinksMarks(this->currentUser.id),
            DBParser::getInstance().getPendingUsersForId(this->currentUser.id));
}

//Transfering data to windowEdit
void MainWindow::on_pushButton_4_clicked()
{  //////////////////TBD NOTHING SELECTED?
    int selectedRow = ui->mainTable->selectionModel()->currentIndex().row();
    QString tempName = ui->mainTable->model()->index(selectedRow,0).data().toString();
    drinkType tempType = getDrinkTypeFromString(ui->mainTable->model()->index(selectedRow,1).data().toString());
    QString tempDescription = ui->mainTable->model()->index(selectedRow,2).data().toString();
    //MEGA CRUTCH
    QPixmap photo = (this->drinkModel->drinksMarks->begin()+ selectedRow).key().photo;//  >begin() + index.row())drinks->operator[](selectedRow).photo;
    int tempId =(this->drinkModel->drinksMarks->begin()+ selectedRow).key().id;
    //int tempId =this->drinkModel->drinks->operator[](selectedRow).id;
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

void MainWindow::on_buttonMark_clicked()
{
    /////////////////TBD NOTHING SELECTED
    int selectedRow = ui->mainTable->selectionModel()->currentIndex().row();
    QString tempName = ui->mainTable->model()->index(selectedRow,0).data().toString();
    QPixmap photo = (this->drinkModel->drinksMarks->begin()+ selectedRow).key().photo;
    int tempId = (this->drinkModel->drinksMarks->begin()+ selectedRow).key().id;
    Drink chosenDrink(tempId,tempName,{},{},photo);
    windowMark->getInitData(chosenDrink,this->currentUser.id);
    windowMark->show();
}


//TBD MOVE GETTING DATA FROM MODEL TO ONE FUNCTION
