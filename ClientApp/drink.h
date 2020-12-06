#ifndef DRINK_H
#define DRINK_H

#include <QAbstractTableModel>
#include <QList>
#include "models.h"
#include <QMap>
#include <QtAlgorithms>


class DrinkModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    QList<Drink> *drinks;

    void clearAll();

    explicit DrinkModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;



    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // DRINK_H
