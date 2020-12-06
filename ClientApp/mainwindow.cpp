#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    windowAdd = new WindowAdd();

    connect(this->windowAdd,SIGNAL(addNewPressed(Drink&)),&DBParser::getInstance(),SLOT(addDrink(Drink&)));
    connect(&DBParser::getInstance(),SIGNAL(successfulLogin(const User&)),this,SLOT(authorize(const User&)));
    drinkModel = new DrinkModel(this);
    ui->mainTable->setModel(drinkModel);



    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authorize(const User &user)
{
    this->show();
    this->currentUser=DBParser::getInstance().getUser(user);
    this->refresh();
    qDebug("OH YEAH MISTER CRABS");
    qDebug()<<currentUser;
}

void MainWindow::refresh()
{
    this->drinkModel->clearAll();
    this->drinkModel->drinks = DBParser::getInstance().getAllDrinks();
}

void MainWindow::on_pushButton_3_clicked()
{
    windowAdd->show();
}
