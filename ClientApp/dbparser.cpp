#include "dbparser.h"

//C2
#include <QFile>


void DBParser::tryLogIn(const User &user){

    if (user.username.isEmpty() || user.password.isEmpty()){
        emit badLogin("Nice input data dude");
        return;
    }

    QSqlQuery query = this->database->getUserData(user);
    query.next();
    if (!query.isValid()){
        emit(badLogin("Such user doesn't exist :("));
    }
    else{
        emit(successfulLogin(user));
    }
}

DBParser &DBParser::getInstance()
{
    static DBParser obj;
    return obj;
}



User &DBParser::getUser(const User &user)
{
    QSqlQuery query  = this->database->getUserData(user);

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



void DBParser::addDrink(Drink &obj){
    QSqlQuery query  = this->database->addDrink(obj,getDrinkTypeId(obj.type));
    emit (dataChanged(getAllDrinks()));
}

void DBParser::updateDrink(Drink &obj)
{
    QSqlQuery query  = this->database->updateDrink(obj,getDrinkTypeId(obj.type));
    emit (dataChanged(getAllDrinks()));
}

int DBParser::getDrinkTypeId(const drinkType &drinkType)
{
    QSqlQuery query = this->database->getDrinkTypeId(drinkType);
    query.next();
    return query.value(0).toInt();
}

Drink DBParser::getDrink(QString &name)
{
    QSqlQuery query = this->database->getDrink(name);
    query.next();
    Drink *result = new Drink;
    QSqlRecord record = query.record();
    result->id = query.value(record.indexOf("id")).toInt();
    result->info = query.value(record.indexOf("info")).toString();
    result->name = query.value(record.indexOf("name")).toString();
    result->type = getDrinkTypeFromString(this->database->getStringOfDrinkTypeId(query.value(record.indexOf("drinks_type_id")).toInt()));
    result->photo.loadFromData(query.value(record.indexOf("photo")).toByteArray(),"PNG");

    return *result;
}

Drink DBParser::getDrink(int &id)
{
    QSqlQuery query = this->database->getDrink(id);
    query.next();
    Drink *result = new Drink;
    QSqlRecord record = query.record();
    result->id = query.value(record.indexOf("id")).toInt();
    result->info = query.value(record.indexOf("info")).toString();
    result->name = query.value(record.indexOf("name")).toString();
    result->type = getDrinkTypeFromString(this->database->getStringOfDrinkTypeId(query.value(record.indexOf("drinks_type_id")).toInt()));
    result->photo.loadFromData(query.value(record.indexOf("photo")).toByteArray(),"PNG");

    return *result;
}

QList<Drink>* DBParser::getAllDrinks()
{
    QSqlQuery query = this->database->getAllDrinks();
    QSqlRecord record = query.record();
    QList<Drink> *result = new QList<Drink>;
    QPixmap *image = new QPixmap;
    while(query.next()){
        image->loadFromData(query.value(record.indexOf("photo")).toByteArray(),"PNG");
        result->append({
                           query.value(record.indexOf("id")).toInt(),
                           query.value(record.indexOf("name")).toString(),
                           query.value(record.indexOf("info")).toString(),
                           getDrinkTypeFromString(this->database->getStringOfDrinkTypeId(query.value(record.indexOf("drinks_type_id")).toInt())),
                           *image
                       });
    }

    delete image;
    return result;
}
