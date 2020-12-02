#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&DBParser::getInstance(),SIGNAL(successfulLogin(const User&)),this,SLOT(authorize(const User&)));

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

}
