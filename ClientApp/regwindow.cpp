#include "regwindow.h"
#include "ui_regwindow.h"

RegWindow::RegWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegWindow)
{
    ui->setupUi(this);
    //tbd
    ui->username->setTabChangesFocus(true);
    ui->password->setTabChangesFocus(true);
    ui->name->setTabChangesFocus(true);
    ui->description->setTabChangesFocus(true);
    setTabOrder(ui->username,ui->password);
    setTabOrder(ui->password,ui->name);
    setTabOrder(ui->name,ui->description);
    setTabOrder(ui->description,ui->buttonBox);

    connect(this,SIGNAL(badInput(const QString&)), this, SLOT(errorMsg(const QString&)));
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text()=="&OK" || button->text()=="OK"){
        if (ui->username->toPlainText().isEmpty()
                || ui->name->toPlainText().isEmpty()
                || ui->password->toPlainText().isEmpty()
                || ui->description->toPlainText().isEmpty())
        {
            emit badInput("Reg data is not filled.");
            return; //maybe not?
        }

        User tempUser{0,ui->username->toPlainText(),
                    ui->name->toPlainText(),
                    ui->password->toPlainText(),
                    true,
                    ui->description->toPlainText()};
        emit(pressedReg(tempUser));



    }
    //emit signal finished? tbd
}

void RegWindow::errorMsg(const QString &obj)
{
    QMessageBox::information(this, "Error",obj);
}
