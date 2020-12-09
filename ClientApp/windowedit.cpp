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

    connect(this,SIGNAL(badInput(const QString&)),this,SLOT(errorMsg(const QString&)));
    connect(&DBParser::getInstance(),SIGNAL(badUpdateData(const QString&)), this, SLOT(errorMsg(const QString&)));
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
    int tempIndexOfComboBox = ui->drinks_types->findData((obj.type));
    this->ui->drinks_types->setCurrentIndex(tempIndexOfComboBox);
    this->hiddenId = obj.id;
}
void WindowEdit::errorMsg(const QString &obj)
{
    QMessageBox::information(this, "Error",obj);
}

//accept/exit buttons TBD FIX NAMES
void WindowEdit::on_buttonBox_clicked(QAbstractButton *button)
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

        Drink *obj = new Drink(this->hiddenId,
                  ui->name->toPlainText(),
                  ui->description->toPlainText(),
                  getDrinkTypeFromString(ui->drinks_types->currentText()),
                  photo);
        emit (editPressed(*obj));
    }
}

//choose image button TBD FIX NAMES
void WindowEdit::on_pushButton_clicked()
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
