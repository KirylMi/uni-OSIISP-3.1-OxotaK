#ifndef WINDOWEDIT_H
#define WINDOWEDIT_H

#include <QDialog>
#include <QAbstractButton>
#include "models.h"
#include "dbparser.h"
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class WindowEdit;
}

class WindowEdit : public QDialog
{
    Q_OBJECT

public:
    explicit WindowEdit(QWidget *parent = nullptr);
    ~WindowEdit();
    void getDrinkData(Drink);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void errorMsg(const QString&);
    void on_pushButton_clicked();

signals:
    void editPressed(Drink &obj);
    void badInput(const QString &input);

private:
    Ui::WindowEdit *ui;
    int hiddenId;
};

#endif // WINDOWEDIT_H
