#include "windowadd.h"
#include "ui_windowadd.h"


//C1

WindowAdd::WindowAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowAdd)
{
    ui->setupUi(this);
    for (int i = firstDrinkType; i<=lastDrinkType; i++){
        ui->drinks_types->addItem(getDrinkTypeString(drinkType(i)));
    }
    connect(this,SIGNAL(badInput(const QString&)),this,SLOT(errorMsg(const QString&)));
}

WindowAdd::~WindowAdd()
{
    delete ui;
}

void WindowAdd::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));


    if (!fileName.isEmpty()){
        QPixmap temp(fileName);
        temp = temp.scaled(ui->photo->width(),ui->photo->height());
        ui->photo->setPixmap(temp);
        qDebug()<<"Chosen drink type: "<<ui->drinks_types->currentText();
        if (ui->name->toPlainText().isEmpty() || ui->description->toPlainText().isEmpty()){
            emit(badInput("Bad input"));
        }
        Drink *obj = new Drink(0,
                  ui->name->toPlainText(),
                  ui->description->toPlainText(),
                  getDrinkTypeFromString(ui->drinks_types->currentText()),
                  temp);
        emit (addNewPressed(*obj));
    }
}
void WindowAdd::errorMsg(const QString &obj)
{
    QMessageBox::information(this, "Error",obj);
}
