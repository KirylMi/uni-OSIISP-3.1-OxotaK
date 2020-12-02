#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(this,SIGNAL(pressedOk(const User&)),&DBParser::getInstance(),SLOT(tryLogIn(const User&)));
    connect(&DBParser::getInstance(),SIGNAL(badLogin(const QString&)),this,SLOT(errorMsg(const QString&)));

    ui->textEdit->setTabChangesFocus(true);
    ui->textEdit_2->setTabChangesFocus(true);
    setTabOrder(ui->textEdit,ui->textEdit_2);
    setTabOrder(ui->textEdit_2,ui->buttonBox);
    setTabOrder(ui->buttonBox,ui->textEdit);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    //OK for windows, &OK for linux (i have literally no idea why is it like that)
    if(button->text()=="&OK" || button->text()=="OK"){
        qDebug("ok");
        const User currentUser{ui->textEdit->toPlainText(),ui->textEdit_2->toPlainText()};
        emit pressedOk(currentUser);
    }
    else{
        qDebug("NotOk");
        emit pressedExit();
    }

    qDebug()<<button->text();
}

void LoginWindow::errorMsg(const QString &obj)
{
    QMessageBox::information(this, "Error",obj);
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<event;
    //event->ignore();
}
