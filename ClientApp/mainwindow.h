#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include "models.h"
#include "dbparser.h"
#include "windowadd.h"
#include "drink.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void authorize(const User&);

private slots:
    void refresh();

    void on_pushButton_3_clicked();

signals:
    void somethingWasPressed();

private:
    Ui::MainWindow* ui;
    User currentUser;
    WindowAdd *windowAdd;
    DrinkModel *drinkModel;

};
#endif // MAINWINDOW_H
