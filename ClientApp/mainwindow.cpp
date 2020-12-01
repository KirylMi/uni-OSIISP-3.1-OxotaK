#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(this,SIGNAL(pressedExit(User)),&DB::getInstance(),SLOT(tryLogIn(User)));
    connect(&DB::getInstance(),SIGNAL(successfulLogin(User)),this,SLOT(authorize(User)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authorize(User)
{
    this->show();
    qDebug("OH YEAH MISTER CRABS");
}
