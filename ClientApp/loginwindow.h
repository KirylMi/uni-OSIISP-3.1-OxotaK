#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include <QMessageBox>
#include "models.h"
#include "db.h"
#include "dbparser.h"
#include <QCloseEvent>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void pressedOk(const User&);
    void pressedExit();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void errorMsg(const QString&);

private:
    Ui::LoginWindow *ui;
    void closeEvent(QCloseEvent *);
};

#endif // LOGINWINDOW_H
