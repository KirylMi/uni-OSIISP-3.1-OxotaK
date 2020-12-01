#include "utils.h"

bool json_hasKey(const QJsonObject &obj, const QString &key){
    return (!obj.value(key).isNull()
            && obj.value(key)!=QJsonValue::Undefined);
}
