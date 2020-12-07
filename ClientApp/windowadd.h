#ifndef WINDOWADD_H
#define WINDOWADD_H

#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include "models.h"

#include <QMessageBox>

namespace Ui {
class WindowAdd;
}

class WindowAdd : public QDialog
{
    Q_OBJECT

public:
    explicit WindowAdd(QWidget *parent = nullptr);
    ~WindowAdd();

private slots:
    void on_pushButton_clicked();
    void errorMsg(const QString&);

    void on_buttonBox_clicked(QAbstractButton *button);

signals:
    void addNewPressed(Drink &obj);
    void badInput(const QString &input);

private:
    Ui::WindowAdd *ui;
};

#endif // WINDOWADD_H
