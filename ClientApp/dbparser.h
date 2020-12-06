#ifndef DBPARSER_H
#define DBPARSER_H

#include <QObject>
#include "QByteArray"
#include "db.h"
#include "models.h"
#include <QList>

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

signals:
    void successfulLogin(const User&);
    void badLogin(const QString&);

public slots:
    void tryLogIn(const User&);

    void addDrink(Drink&);

    Drink getDrink(QString &name);
    Drink getDrink(int &id);
    QList<Drink>* getAllDrinks();

};

#endif // DBPARSER_H
