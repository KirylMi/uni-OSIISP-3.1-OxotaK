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
    QSqlQuery q2("INSERT INTO \"oxotaK\".drinks_type (type) VALUES('Beer');");
    QSqlQuery q3("INSERT INTO \"oxotaK\".drinks_type (type) VALUES('Soda');");
    QSqlQuery q4("INSERT INTO \"oxotaK\".drinks_type (type) VALUES('Vodka');");
    QSqlQuery drinkNames("SELECT * FROM \"oxotaK\".drinks_type");
    QSqlQuery("UPDATE \"oxotaK\".users SET password = '098f6bcd4621d373cade4e832627b4f6' WHERE id = 1;");
    for (int i=0;i<drinkNames.size();i++){
        drinkNames.next();
        //if (i==0) QSqlQuery("INSERT INTO \"oxotaK\".drinks(name, info, drinks_type_id) VALUES ('Hello', 'That''s a good one', '" + drinkNames.value(0).toString() + "');");
        //if (i==1) QSqlQuery("INSERT INTO \"oxotaK\".drinks(name, info, drinks_type_id) VALUES ('Cola', 'That''s a popular one', '" + drinkNames.value(0).toString() + "');");
        //if (i==2) QSqlQuery("INSERT INTO \"oxotaK\".drinks(name, info, drinks_type_id) VALUES ('KYMI', 'That''s a bad one', '" + drinkNames.value(0).toString() + "');");
        if (i!=0 && i!=1 && i!=2){
            qDebug("GG");
        }

    }
    //QSqlQuery q2("INSERT INTO \"oxotaK\".users (username, name, password, description) VALUES ('Dendel228', 'C0K01', 'hash', 'Foundation member of OK');");
    //QSqlQuery q3("SELECT * FROM \"oxotaK\".users");
    //while (q3.next()) {
     //       qDebug()<<q3.value("email").toString();
     //   }
    //q2.exec();

}

MainWindow::~MainWindow()
{
    delete ui;
}

