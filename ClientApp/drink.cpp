#include "drink.h"

void DrinkModel::clearAll()
{
    this->drinksMarks->clear();
}

//void DrinkModel::refresh(QList<Drink> *newList)
//{
//    this->beginResetModel();
//    if (newList){
//        this->clearAll();
//        this->drinks = newList;
//    }
//    this->endResetModel();
//}
void DrinkModel::refresh(QMap<Drink,int> *newList)
{
    this->beginResetModel();
    if (newList){
        this->clearAll();
        this->drinksMarks = newList;
    }
    this->endResetModel();
}

void DrinkModel::refresh(QList<Drink> *newList)
{
    this->beginResetModel();
    QMap<Drink, int>* newMap = new QMap<Drink,int>;
    for (auto drink : *newList){
        /////auto it = std::find_if(drinksMarks->begin(),drinksMarks->end(),[&drink](QPair<Drink,int> val){ ?
        auto it = std::find_if(drinksMarks->keyBegin(),drinksMarks->keyEnd(),[&drink](Drink val){
            return val.id==drink.id;
        }); //id doesn't change, so. Though if multi users at the same time.... it might be a problem (fix -> end() check)
        if (it!=drinksMarks->keyEnd())
            newMap->insert(drink,drinksMarks->operator[](*it));
        else{
                newMap->insert(drink,0);
            }
    }
    this->drinksMarks->swap(*newMap);
    this->endResetModel();
    //Delete newMap (which is oldMap now)?
}

DrinkModel::DrinkModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    this->drinksMarks = new QMap<Drink,int>;
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

    return drinksMarks->count();
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

    //const auto& drink = drinksMarks[1];  ->operator[](index.row());
    const auto& drink = (drinksMarks->begin() + index.row()).key();
    switch(index.column()){
    case 0: return drink.name;
    case 1: return getDrinkTypeString(drink.type);
    case 2: return drink.info;
    case 3: return (drinksMarks->begin() + index.row()).value();
    default: return "???????????";
    }
}
