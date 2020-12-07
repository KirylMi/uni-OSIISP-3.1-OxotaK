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
                                                    tr("Images (*.png)"));
    if (!fileName.isEmpty()){
        QPixmap temp(fileName);
        temp = temp.scaled(ui->photo->width(),ui->photo->height());
        ui->photo->setPixmap(temp);
    }

}
void WindowAdd::errorMsg(const QString &obj)
{
    QMessageBox::information(this, "Error",obj);
}

void WindowAdd::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text()=="&OK" || button->text()=="OK"){
        qDebug()<<"Chosen drink type: "<<ui->drinks_types->currentText();

        auto photo = ui->photo->pixmap(Qt::ReturnByValue);

        if (ui->name->toPlainText().isEmpty()
                || ui->description->toPlainText().isEmpty()
                || photo.isNull())
        {
            emit(badInput("Bad input"));
            return;
        }

        Drink *obj = new Drink(0,
                  ui->name->toPlainText(),
                  ui->description->toPlainText(),
                  getDrinkTypeFromString(ui->drinks_types->currentText()),
                  photo);
        emit (addNewPressed(*obj));
    }

}
