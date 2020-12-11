#include "windowmark.h"
#include "ui_windowmark.h"

WindowMark::WindowMark(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowMark)
{
    ui->setupUi(this);
    connect(this,SIGNAL(badInput(const QString&)),this,SLOT(errorMsg(const QString&)));
}

WindowMark::~WindowMark()
{
    delete ui;
}

void WindowMark::getInitData(Drink obj, int id)
{
    this->ui->name->setText(obj.name);
    this->ui->photo->setPixmap(obj.photo);
    this->hiddenIdOfDrink=obj.id;
    this->hiddenIdOfUser=id;
}

void WindowMark::errorMsg(const QString &obj)
{
    QMessageBox::information(this, "Error",obj);
}

void WindowMark::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text()=="&OK" || button->text()=="OK"){
        if (ui->sliderMark->value()<=0
                || ui->sliderMark->value()>5
                || ui->comment->toPlainText().isEmpty()){
            emit (badInput("Wrong data"));
            return;
        }
        Drink tempDrink{this->hiddenIdOfDrink,{},{},{},{}};
        emit(markPressed(
                        tempDrink,
                        ui->comment->toPlainText(),
                        ui->sliderMark->value(),
                        this->hiddenIdOfUser));
    }
}
