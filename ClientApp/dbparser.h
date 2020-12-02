#ifndef DBPARSER_H
#define DBPARSER_H

#include <QObject>
#include "db.h"

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

};

#endif // DBPARSER_H
