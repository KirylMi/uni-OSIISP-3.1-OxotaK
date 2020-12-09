#include "regwindow.h"
#include "ui_regwindow.h"

RegWindow::RegWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegWindow)
{
    ui->setupUi(this);
    //tbd
    ui->textEdit->setTabChangesFocus(true);
    ui->textEdit_2->setTabChangesFocus(true);
    ui->textEdit_3->setTabChangesFocus(true);
    setTabOrder(ui->textEdit,ui->textEdit_2);
    setTabOrder(ui->textEdit_2,ui->textEdit_3);
    setTabOrder(ui->textEdit_3,ui->buttonBox);

    connect(this,SIGNAL(badInput(const QString&)), this, SLOT(errorMsg(const QString&)));
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text()=="&OK" || button->text()=="OK"){
        if (ui->textEdit->toPlainText().isEmpty()
                || ui->textEdit_2->toPlainText().isEmpty()
                || ui->textEdit_3->toPlainText().isEmpty())
        {
            emit badInput("Reg data is not filled.");
            return; //maybe not?
        }



    }
    //emit signal finished? tbd
}

void RegWindow::errorMsg(const QString &obj)
{
    QMessageBox::information(this, "Error",obj);
}
