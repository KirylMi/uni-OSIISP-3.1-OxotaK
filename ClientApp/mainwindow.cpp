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
    connect(&DBParser::getInstance(),SIGNAL(successfulLogin(const User&)),this,SLOT(authorize(const User&)));

    drinkModel = new DrinkModel(this);
    drinkModel->drinks =  DBParser::getInstance().getAllDrinks();

    ui->mainTable->setModel(drinkModel);
    ui->mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mainTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->mainTable->setColumnWidth(0,150);
    ui->mainTable->setColumnWidth(1,150);
    ui->mainTable->setColumnWidth(2,320);
    ui->mainTable->setColumnWidth(3,100);

    ui->mainTable->horizontalHeader()->setVisible(true);
    ui->mainTable->show();


    //refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authorize(const User &user)
{
    this->show();
    qDebug()<<this->ui->mainTable->model()->data(ui->mainTable->model()->index(0,0));
    this->currentUser=DBParser::getInstance().getUser(user);
    //this->refresh();
    qDebug("OH YEAH MISTER CRABS");
    qDebug()<<currentUser;
}

void MainWindow::refresh()
{
    this->drinkModel->clearAll();
    //this->drinkModel->drinks = DBParser::getInstance().getAllDrinks();

}

void MainWindow::on_pushButton_3_clicked()
{
    windowAdd->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    refresh();
}

void MainWindow::on_pushButton_4_clicked()
{
    Drink tempChosenDrink;
    int selectedRow = ui->mainTable->selectionModel()->currentIndex().row();
    QString tempName = ui->mainTable->model()->index(selectedRow,0).data().toString();
    drinkType tempType = getDrinkTypeFromString(ui->mainTable->model()->index(selectedRow,1).data().toString());
    QString tempDescription = ui->mainTable->model()->index(selectedRow,2).data().toString();
    //MEGA CRUTCH
    QPixmap photo = this->drinkModel->drinks->operator[](selectedRow).photo;
    int tempId =this->drinkModel->drinks->operator[](selectedRow).id;
    Drink chosenDrink(tempId,tempName,tempDescription,tempType,photo);
    windowEdit->getDrinkData(chosenDrink);
    windowEdit->show();
}
