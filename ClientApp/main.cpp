#include "mainwindow.h"
#include "db.h"
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    DB::getInstance();
    LoginWindow loginWindow;

    loginWindow.show();

    return a.exec();
}
