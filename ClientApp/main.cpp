#include "mainwindow.h"
#include "db.h"
#include "loginwindow.h"
#include "dbparser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    DBParser::getInstance();
    LoginWindow loginWindow;

    loginWindow.show();

    return a.exec();
}

//tbd int getID of drink from Db to dbparser
