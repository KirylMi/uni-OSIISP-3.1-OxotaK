#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include "models.h"
#include "db.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void pressedOk(User&);
    void pressedExit();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void errorMsg(const QString&);

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
