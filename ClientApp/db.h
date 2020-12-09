#ifndef DB_H
#define DB_H

#include "models.h"
#include "utils.h"
#include <QSqlDatabase>
#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QVector>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlRecord>
#include <QSqlRecord>
#include <QBuffer>
#include <QByteArray>
#include "dbparser.h"

class DBParser;

class DB : public QObject {
    Q_OBJECT
public:
    DB();
    friend DBParser;

private:

    QSqlDatabase database;
    QVector<QString> params{"HostName","DatabaseName","UserName","Password","Port", "Schema"};

    QString schema;
    QString getSchemaUsers();
    QString getSchemaReviews();
    QString getSchemaDrinksType();
    QString getSchemaDrinks();
    QString getSchemaApproval();

    QString getStringOfDrinkTypeId(const int &val);

signals:
    void error(const QString&);

public slots:
    QSqlQuery& getUserData(const User&);
    QSqlQuery& addDrink(const Drink&, const int& drinkTypeId);
    QSqlQuery& updateDrink(const Drink&, const int& drinkTypeId);

    QSqlQuery& regUser(const User&);

    QSqlQuery& getDrinkTypeId(const drinkType&);


    QSqlQuery& getDrink(int &id);
    QSqlQuery& getDrink(QString &name);
    QSqlQuery& getAllDrinks();
};

#endif // DB_H
