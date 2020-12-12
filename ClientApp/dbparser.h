#ifndef DBPARSER_H
#define DBPARSER_H

#include <QObject>
#include <QDebug>
#include "QByteArray"
#include "db.h"
#include "models.h"
#include <QList>
#include <QMap>
#include <QPair>

class DB;

class DBParser : public QObject
{
    Q_OBJECT
public:
    static DBParser& getInstance();
    User& getUser(const User &user);


private:
    DBParser();
    DBParser& operator=(const DBParser&);
    DBParser(const DBParser&);

    DB *database;

    void approveUser(const User&);

signals:
    void successfulLogin(const User&);
    void badLogin(const QString&);
    void badNewData(const QString&);
    void badUpdateData(const QString&);
    void badRegData(const QString&);
    void dataChanged(QList<Drink>*, QList<User>*);
    void dataChanged(QMap<Drink,int>*, QList<User>*);
    //cratch? tbd
    void dataChanged(QList<User>*);

public slots:
    void tryLogIn(const User&);

    void addDrink(Drink&);
    void updateDrink(Drink&);
    void rankDrink(Drink&, const QString& comment, const int &mark, const int&id);
    void deleteDrink(Drink&);

    int getDrinkTypeId(const drinkType&);

    Drink getDrink(QString &name);
    Drink getDrink(int &id);
    QList<Drink>* getAllDrinks();
    QMap<Drink,int>* getAllDrinksMarks(const int &id);

    QList<User>* getPendingUsersForId(const int &id);
    QList<User>* getAllPendingUsers();
    int getAllPendingUsersCount();

    void regUser(const User &user);

    void addApproval(const User&, const int &id);

};

#endif // DBPARSER_H
