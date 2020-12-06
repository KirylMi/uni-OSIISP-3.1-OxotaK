#ifndef WINDOWEDIT_H
#define WINDOWEDIT_H

#include <QDialog>
#include "models.h"
#include "dbparser.h"

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

private:
    Ui::WindowEdit *ui;
};

#endif // WINDOWEDIT_H
