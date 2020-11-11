#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase obj = QSqlDatabase::addDatabase("QPSQL");
    obj.setHostName("localhost");
    obj.setDatabaseName("myDb");
    obj.setUserName("postgres");
    obj.setPassword("test");
    obj.setPort(5432);
    obj.open();
    qDebug()<<obj.isOpen();
    qDebug()<<obj.isOpenError();
    qDebug()<<obj.lastError().text();
//    QSqlQuery q("SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE='BASE TABLE'");
//    QSqlRecord rec = q.record();
//    qDebug()<<"Number of columns"<<rec.count();
//    while (q.next()){
//                QString name = q.value(0).toString();
//                qDebug()<<"name:"<<name;
//            }
    QSqlQuery q2("INSERT INTO public.users (email, username, password, privilege, name) VALUES ('another22238@gmail.com', 'anotherUserName28', 'password', 'admin', 'name38');");
    //q2.exec();

}

MainWindow::~MainWindow()
{
    delete ui;
}

