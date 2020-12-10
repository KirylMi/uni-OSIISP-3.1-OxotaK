#ifndef USERMODEL_H
#define USERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "models.h"

class UserModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit UserModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void clearAll();
    void refresh(QList<User>* = nullptr);
    QList<User> *users;
private:
};

#endif // USERMODEL_H
