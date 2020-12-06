#include "drink.h"

void DrinkModel::clearAll()
{
    this->drinks->clear();
}

DrinkModel::DrinkModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    this->drinks = new QList<Drink>;
}

QVariant DrinkModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(section){
    case 0: return "Name";
    case 1: return "Type";
    case 2: return "Description";
    case 3: return "MyMark";
    default: return {};
    }
}

QModelIndex DrinkModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex DrinkModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int DrinkModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return drinks->count();
}

int DrinkModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    return 4;
}

QVariant DrinkModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto& drink = drinks->operator[](index.row());
    switch(index.column()){
    case 0: return drink.name;
    case 1: return drink.type;
    case 2: return drink.info;
    case 3: return "TBD";
    default: return "TBDDef";
    }
}
