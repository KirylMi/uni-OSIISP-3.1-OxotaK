#ifndef MODELS_H
#define MODELS_H

#include <QObject>
#include <QDebug>

struct User{
    User(){};
    User(QString username, QString password)
        : username(username), password(password){};
    User(int id, QString username, QString name, QString password, bool isActive, QString description)
        :id(id),username(username),name(name),password(password),isActive(isActive),description(description){};
    User(const User &other)
        :id(other.id),username(other.username),name(other.name),password(other.password),isActive(other.isActive),description(other.description){};
    int id;
    QString username;
    QString name;
    QString password;
    bool isActive;
    QString description;
    friend QDebug operator<<(QDebug debug, const User &user);
};

enum drinkType{
    Beer,
    Soda,
    Vodka
};

struct Drink{
    Drink(){};
    Drink(int id, QString name, QString info, drinkType type)
        :id(id),name(name),info(info),type(type){};
    Drink (const Drink &other)
        :id(other.id),name(other.name),info(other.info),type(other.type){};
    int id;
    QString name;
    QString info;
    drinkType type;
};

#endif // MODELS_H
