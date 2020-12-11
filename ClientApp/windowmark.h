#ifndef WINDOWMARK_H
#define WINDOWMARK_H

#include <QDialog>
#include "models.h"
#include <QMessageBox>
#include <QAbstractButton>

namespace Ui {
class WindowMark;
}

class WindowMark : public QDialog
{
    Q_OBJECT

public:
    explicit WindowMark(QWidget *parent = nullptr);
    ~WindowMark();
    void getInitData(Drink, int);

private slots:
    void errorMsg(const QString&);

    void on_buttonBox_clicked(QAbstractButton *button);

signals:
    void markPressed(Drink&,const QString& comment, const int &mark, const int& userId);
    void badInput(const QString &input);

private:
    Ui::WindowMark *ui;

    int hiddenIdOfDrink;
    int hiddenIdOfUser;
};

#endif // WINDOWMARK_H
