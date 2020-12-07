#include "db.h"


//DB& DB::getInstance(){
//    static DB obj;
//    return obj;
//}



DB::DB()
    :database(QSqlDatabase::addDatabase("QPSQL"))
{
    QFile file;
    if (!file.exists(":/env/env.json"))
        throw new std::runtime_error("No env file");
    file.setFileName(":/env/env.json");
    //bad practice, yeah, but it's kinda ok with singleton, and the program should finish if file isn't opened, so...
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.isOpen())
        throw new std::runtime_error ("Nice env file dude");

    QString content;
    content = file.readAll();
    QJsonObject jsonObj = QJsonDocument::fromJson(content.toUtf8()).object();

    for(auto &i : params){
        if (!json_hasKey(jsonObj,i)) throw new std::runtime_error ("Nice env file content dude");
    }


    this->database.setDatabaseName(jsonObj.value("DatabaseName").toString());
    this->database.setHostName(jsonObj.value("HostName").toString());
    this->database.setUserName(jsonObj.value("UserName").toString());
    this->database.setPassword(jsonObj.value("Password").toString());
    this->database.setPort(jsonObj.value("Port").toInt());

    this->database.open();
    if(!this->database.isOpen()){
        qDebug()<<this->database.lastError().text();
        throw new std::runtime_error("Nice database dude");
    }

    this->schema=jsonObj.value("Schema").toString();

}

QString DB::getSchemaUsers()
{
    return QString('\"' + this->schema + '\"' + ".users");
}

QString DB::getSchemaReviews()
{
    return QString('\"' + this->schema + '\"' + ".reviews");
}

QString DB::getSchemaDrinksType()
{
    return QString('\"' + this->schema + '\"' + ".drinks_type");
}

QString DB::getSchemaDrinks()
{
    return QString('\"' + this->schema + '\"' + ".drinks");
}

QString DB::getSchemaApproval()
{
    return QString('\"' + this->schema + '\"' + ".approval");
}

QSqlQuery& DB::getUserData(const User &user)
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT * FROM " + getSchemaUsers() + " WHERE username = :username AND password = :password");
    qDebug().noquote()<<"SELECT * FROM " + getSchemaUsers()  + " WHERE username = :username AND password = :password";
    query->bindValue(":username",user.username);
    query->bindValue(":password",QString(QCryptographicHash::hash((user.password.toUtf8()),QCryptographicHash::Md5).toHex()));

    if(!query->exec()){  //tdb maybe all on the parser? No emits from DB TDB
        emit(error("DB doesn't respond (tryLogIn function)"));
    }
    return *query;
}


QSqlQuery& DB::getDrinkTypeId(const drinkType& type){
    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT id FROM " + getSchemaDrinksType() + " WHERE type = :type");
    query->bindValue(":type", getDrinkTypeString((type)));
    qDebug()<<"Bind val: "<<getDrinkTypeString(type);
    if (!query->exec()){
        emit error("DB doesn't respond (getDrinkTypeId function)");
    }
    return *query;
}

QString DB::getStringOfDrinkTypeId(const int &val){
    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT type FROM " + getSchemaDrinksType() + " WHERE id = :id");
    query->bindValue(":id", val);
    qDebug()<<"Bind val: "<<val;
    query->exec();
    query->next();
    return query->value(0).toString();
}

QSqlQuery &DB::getDrink(int &id)
{
    QSqlQuery *query = new QSqlQuery;
    query->exec("SELECT * FROM " + getSchemaDrinks() + " WHERE id = '" + id + '\'');
    return *query;
}

QSqlQuery &DB::getDrink(QString &name)
{
    QSqlQuery *query = new QSqlQuery;
    query->exec("SELECT * FROM " + getSchemaDrinks() + " WHERE name = '" + name + '\'');
    return *query;
}

QSqlQuery &DB::getAllDrinks()
{
    QSqlQuery *query = new QSqlQuery;
    query->exec("SELECT * FROM " + getSchemaDrinks());
    return *query;
}

QSqlQuery& DB::addDrink(const Drink &drink,  const int& drinkTypeId){
    QSqlQuery *query = new QSqlQuery;
    query->prepare("INSERT INTO " + getSchemaDrinks() + "( "
                   "name, photo, info, drinks_type_id)"
                   " VALUES (:name, :photo, :info, :drinks_type_id);");
    query->bindValue(":drinks_type_id",drinkTypeId);
    qDebug()<<"bind value: "<<drinkTypeId;
    query->bindValue(":name",drink.name);
    QByteArray byteArr;
    QBuffer buffer(&byteArr);
    buffer.open(QIODevice::WriteOnly);
    drink.photo.save(&buffer,"PNG");
    query->bindValue(":photo",buffer.data());
    query->bindValue(":info",drink.info);
    query->exec();
    return *query;
}

QSqlQuery &DB::updateDrink(const Drink &drink, const int &drinkTypeId)
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("UPDATE " + getSchemaDrinks() + " " +
                   "SET name=:name, photo=:photo, info=:info, drinks_type_id=:drinks_type_id "
                   "WHERE id = :id;");
    query->bindValue(":id",drink.id);
    query->bindValue(":drinks_type_id",drinkTypeId);
    qDebug()<<"bind value: "<<drinkTypeId;
    query->bindValue(":name",drink.name);
    QByteArray byteArr;
    QBuffer buffer(&byteArr);
    buffer.open(QIODevice::WriteOnly);
    drink.photo.save(&buffer,"PNG");
    query->bindValue(":photo",buffer.data());
    query->bindValue(":info",drink.info);
    query->exec();
    return *query;
}
