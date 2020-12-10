#include "user.h"

UserModel::UserModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    this->users = new QList<User>;
}

void UserModel::clearAll()
{
    this->users->clear();
}

void UserModel::refresh(QList<User> *newList)
{
    this->beginResetModel();
    if (newList){
        this->clearAll();
        this->users = newList;
    }
    this->endResetModel();
}

QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role!=Qt::DisplayRole){
        return QVariant();
    }
    if (orientation==Qt::Horizontal){
        switch(section){
        case 0: return "Name";
        case 1: return "Description";
        default: return {};
        }
    }
    //{} == QVariant() in this case, not sure why i'm commenting this.
    return QVariant();
}

int UserModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return users->count();
}

int UserModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 2;
}

QVariant UserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role!=Qt::DisplayRole)
        return QVariant();

    const auto& user = this->users->operator[](index.row());
    switch(index.column()){
    case 0: return user.name;
    case 1: return user.description;
    default: return {};
    }

    return QVariant();
}
