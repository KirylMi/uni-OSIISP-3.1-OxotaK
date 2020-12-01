#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

bool json_hasKey(const QJsonObject &obj, const QString &key);

#endif // UTILS_H
