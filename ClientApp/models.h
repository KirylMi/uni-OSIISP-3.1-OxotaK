#ifndef MODELS_H
#define MODELS_H

#include <QObject>
#include <QDebug>
#include <QPixmap>

struct User{
    User(){};
    User(QString username, QString password)
        : username(username), password(password){};
    User(int id, QString username, QString name, QString password, bool isActive, QString description)
        :id(id),username(username),name(name),password(password),isActive(isActive),description(description){};
    User(const User &other)
        :id(other.id),username(other.username),name(other.name),password(other.password),isActive(other.isActive),description(other.description){};
    User& operator = (const User&other){
        this->id = other.id;
        this->description=other.description;
        this->isActive=other.isActive;
        this->name=other.name;
        this->password=other.password;
        this->username=other.username;
        return *this;
    }
    int id;
    QString username;
    QString name;
    QString password;
    bool isActive;
    QString description;
    friend QDebug operator<<(QDebug debug, const User &user);
};

enum drinkType{
    Soda,
    Beer,
    Vodka,
    UNDEFINED,
    firstDrinkType=Soda,
    lastDrinkType=Vodka
};

    QString getDrinkTypeString(drinkType drinkType);
drinkType getDrinkTypeFromString(QString str);

struct Drink{
    Drink(){};
    Drink(int id, QString name, QString info, drinkType type, QPixmap photo)
        :id(id),name(name),info(info),type(type),photo(photo){};
    Drink (const Drink &other)
        :id(other.id),name(other.name),info(other.info),type(other.type),photo(other.photo){};
    Drink& operator = (const Drink& other) = default;
    int id;
    QString name;
    QString info;
    drinkType type;
    QPixmap photo;
};

#endif // MODELS_H
