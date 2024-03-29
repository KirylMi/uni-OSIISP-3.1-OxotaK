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
        if (query.value(query.record().indexOf("is_active")).toBool()==true){
            emit(successfulLogin(user));
        }
        else{
            emit badLogin("Such user is not yet activated");
        }
    }
}

void DBParser::regUser(const User &user){
    if (user.username.isEmpty()
            || user.password.isEmpty()
            || user.description.isEmpty()
            || user.name.isEmpty())
    {
        emit badLogin("Nice input data dude");
        return;
    }

    QSqlQuery query = this->database->regUser(user);
    query.next();
    //TBD active or valid?
    if (!query.isActive()){
        emit badRegData("Such user already exists");
    }
}

void DBParser::approveUser(const User &user)
{
    //tbd checkers
    QSqlQuery query = this->database->approveUser(user);
    query.next();
    //tbd
}

void DBParser::addApproval(const User &user, const int &id)
{
    QSqlQuery query = this->database->addApproval(user,id);
    query.next();
    //tbd check, if query failed, it means something really sad :(

    query  = this->database->getApproversOf(user.id);

    int approversOfUserCount = 0;
    if(query.last())
    {
        approversOfUserCount =  query.at() + 1;
        query.first();
        query.previous();
    }

    query = this->database->getAllActiveUsersCount();
    query.next();
    int activeUsersCount = query.value(0).toInt();


    if (approversOfUserCount == activeUsersCount){
        approveUser(user);
    }
    emit (dataChanged(getPendingUsersForId(id)));
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
    query.next();
    if (query.isActive()){
        qDebug()<<"Is valid!";
    }
    else{
        emit badNewData("Such drink, probably, already exists");
        qDebug()<<"Isn't valid!";
    }


    emit (dataChanged(getAllDrinks(),nullptr));
}

void DBParser::updateDrink(Drink &obj)
{
    QSqlQuery query  = this->database->updateDrink(obj,getDrinkTypeId(obj.type));
    query.next();
    if (query.isActive()){
        qDebug()<<"Is valid!";
    }
    else{
        emit badUpdateData("Such drink, probably, already exists");
        qDebug()<<"Isn't valid!";
    }

    emit (dataChanged(getAllDrinks(),nullptr));
}

void DBParser::rankDrink(Drink &drink, const QString &comment, const int &mark, const int &id)
{//check? tbd
    QSqlQuery query = this->database->rankDrink(drink,comment,mark,id);
    query.next();
    emit dataChanged(getAllDrinksMarks(id),nullptr);
}

void DBParser::deleteDrink(Drink &obj)
{
    QSqlQuery query = this->database->deleteDrink(obj);
    query.next();
    emit dataChanged(getAllDrinks(), nullptr);
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

QMap<Drink, int> *DBParser::getAllDrinksMarks(const int &userId)
{
    QList<Drink>* drinks= getAllDrinks();

    QSqlQuery queryMarks = this->database->getAllMarks(userId);
    QSqlRecord recordMarks = queryMarks.record();

    QMap<int,int> tempMarksIDs;

    QMap<Drink,int> *result = new QMap<Drink,int>;

    while(queryMarks.next()){
        tempMarksIDs[queryMarks.value(recordMarks.indexOf("drinks_id")).toInt()]=
                               queryMarks.value(recordMarks.indexOf("mark")).toInt();
    }
    for (auto drink : *drinks){ //one of the ways, i've decided to make a copy with deletion instead of referensing and no deletion
        auto val = tempMarksIDs.find(drink.id);
        if (val!=tempMarksIDs.end()){
            //does it make a copy here? If it does, & above should be added after all... tbd
            result->insert(drink,val.value());
        }
        else{
            result->insert(drink,0);
        }
    }
    return result;
}

QList<User> *DBParser::getPendingUsersForId(const int &id)
{
    QSqlQuery query = this->database->getPendingUsersForId(id);
    QSqlRecord record = query.record();
    QList<User> *result = new QList<User>;
    while (query.next()){
        //might give a warning due to the SELECT query, which return only id,username and descript, but no actual problem here anyway.
        result->append({
                           query.value(record.indexOf("id")).toInt(),
                           query.value(record.indexOf("username")).toString(),
                           query.value(record.indexOf("name")).toString(),
                           query.value(record.indexOf("password")).toString(),
                           query.value(record.indexOf("is_active")).toBool(),
                           query.value(record.indexOf("description")).toString(),
                       });
    }

    return result;

}

QList<User> *DBParser::getAllPendingUsers()
{
    QSqlQuery query = this->database->getAllPendingUsers();
    QSqlRecord record = query.record();
    QList<User> *result = new QList<User>;
    while (query.next()){
        result->append({
                           query.value(record.indexOf("id")).toInt(),
                           query.value(record.indexOf("username")).toString(),
                           query.value(record.indexOf("name")).toString(),
                           query.value(record.indexOf("password")).toString(),
                           query.value(record.indexOf("is_active")).toBool(),
                           query.value(record.indexOf("description")).toString(),
                       });
    }
    return result;
}

int DBParser::getAllPendingUsersCount()
{
    QSqlQuery query = this->database->getAllPendingUsersCount();
    query.next();
    return query.value(0).toInt();
}
