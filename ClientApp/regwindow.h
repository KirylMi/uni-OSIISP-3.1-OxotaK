#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QMessageBox>
#include "models.h"

namespace Ui {
class RegWindow;
}

class RegWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = nullptr);
    ~RegWindow();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void errorMsg(const QString &obj);

signals:
    void badInput(const QString &input);
    void pressedReg(const User&);

private:
    Ui::RegWindow *ui;
};

#endif // REGWINDOW_H
