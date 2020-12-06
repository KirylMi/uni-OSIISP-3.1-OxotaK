#include "windowedit.h"
#include "ui_windowedit.h"

WindowEdit::WindowEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowEdit)
{
    ui->setupUi(this);
    for (int i = firstDrinkType; i<=lastDrinkType; i++){
        ui->drinks_types->addItem(getDrinkTypeString(drinkType(i)),drinkType(i));
    }
}

WindowEdit::~WindowEdit()
{
    delete ui;
}

void WindowEdit::getDrinkData(Drink obj)
{
    this->ui->name->setText(obj.name);
    this->ui->description->setText(obj.info);
    this->ui->photo->setPixmap(obj.photo);
    qDebug()<<getDrinkTypeString(obj.type);
    //qDebug()<<ui->drinks_types->currentData();
    int tempIndexOfComboBox = ui->drinks_types->findData((obj.type));
    this->ui->drinks_types->setCurrentIndex(tempIndexOfComboBox);
}
