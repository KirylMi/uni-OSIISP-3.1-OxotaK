#ifndef DB_H
#define DB_H

#include <QObject>

class DB : public QObject
{
    Q_OBJECT
public:
    explicit DB(QObject *parent = nullptr);

signals:

};

#endif // DB_H
