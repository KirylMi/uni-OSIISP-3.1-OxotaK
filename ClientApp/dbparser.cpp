#include "dbparser.h"

void DBParser::tryLogIn(const User &user){
    //if username+pass not empty tbd
    QSqlQuery query = this->database->getUserData(user);
    query.next();
    if (!query.isValid()){
        emit(badLogin("Such user doesn't exist :("));
        //return false;
    }
    else{
        emit(successfulLogin(user));
    }
    //return true;
}

DBParser &DBParser::getInstance()
{
    static DBParser obj;
    return obj;

}

User &DBParser::getUser(const User &user)
{
    QSqlQuery query  = this->database->getUserData(user);
    //tdb DRY ^^^ (canLogIn Function)
    query.next();
    User *result = new User;
    if (!query.isValid()){
        emit(badLogin("Such user doesn't exist :("));
        return *result;
    }
    qDebug("Successful select of the user from the DB");

    QSqlRecord record = query.record();

    if (!query.value(record.indexOf("is_active")).toBool()){
        emit(badLogin("User is not yet activated")); //tdb add list of pending activations
        return *result;
    }

    result->id=query.value(record.indexOf("id")).toInt();
    result->name=query.value(record.indexOf("name")).toString();
    result->description = query.value(record.indexOf("description")).toString();
    result->isActive=query.value(record.indexOf("is_active")).toBool();
    result->username = query.value(record.indexOf("username")).toString();
    result->password = query.value(record.indexOf("password")).toString();
    qDebug()<<result;
    //tdb check integrity
    return *result;
}

DBParser::DBParser()
{
    this->database = new DB();
}
