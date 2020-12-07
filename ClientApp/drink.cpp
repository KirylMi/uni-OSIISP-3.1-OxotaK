#include "drink.h"

void DrinkModel::clearAll()
{
    this->drinks->clear();
}

void DrinkModel::refresh(QList<Drink> *newList)
{
    this->beginResetModel();
    if (newList){
        this->clearAll();
        this->drinks = newList;
    }
    this->endResetModel();
}

DrinkModel::DrinkModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    this->drinks = new QList<Drink>;
}

QVariant DrinkModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation==Qt::Horizontal){
        switch(section){
        case 0: return "Name";
        case 1: return "Type";
        case 2: return "Description";
        case 3: return "MyMark";
        default: return {};
        }
    }
    return QVariant();
}

int DrinkModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    //if (!parent.isValid())
    //    return 0;

    return drinks->count();
}

int DrinkModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    //if (!parent.isValid())
    //    return 0;
    return 4;
}

QVariant DrinkModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role!=Qt::DisplayRole)
        return QVariant();

    const auto& drink = drinks->operator[](index.row());
    switch(index.column()){
    case 0: return drink.name;
    case 1: return getDrinkTypeString(drink.type);
    case 2: return drink.info;
    case 3: return "TBD";
    default: return "TBDDef";
    }
}
