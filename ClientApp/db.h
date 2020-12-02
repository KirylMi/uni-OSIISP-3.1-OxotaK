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


class DB : public QObject {
    Q_OBJECT
public:
    static DB& getInstance();
    bool canLogIn(const QString& username, const QString& password);
    bool canLogIn(const User& obj);

private:
    DB();
    DB& operator=(const DB&);
    DB(const DB&);

    QSqlDatabase database;
    QVector<QString> params{"HostName","DatabaseName","UserName","Password","Port", "Schema"};

    QString schema;
    QString getSchemaUsers();
    QString getSchemaReviews();
    QString getSchemaDrinksType();
    QString getSchemaDrinks();
    QString getSchemaApproval();

signals:
    void successfulLogin(User);
    void badLogin(const QString&);

public slots:
    void tryLogIn(User&);
};

#endif // DB_H
