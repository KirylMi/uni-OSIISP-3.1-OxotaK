#include "db.h"


DB& DB::getInstance(){
    static DB obj;
    return obj;
}



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
    //connect(this,SIGNAL(pressedExit(User)),&DB::getInstance(),SLOT(tryLogIn(User)));
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

void DB::tryLogIn(User &user)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM " + getSchemaUsers() + " WHERE username = :username AND password = :password");
    qDebug().noquote()<<"SELECT * FROM " + getSchemaUsers()  + " WHERE username = :username AND password = :password";
    query.bindValue(":username",user.username);
    query.bindValue(":password",QString(QCryptographicHash::hash((user.password.toUtf8()),QCryptographicHash::Md5).toHex()));

    if(query.exec()){
        query.next();
        if (!query.isValid()){
            emit(badLogin("Such user doesn't exist :("));
            return;
        }
        qDebug("Successful select of the user from the DB");

        QSqlRecord record = query.record();

        if (!query.value(record.indexOf("is_active")).toBool()){
            emit(badLogin("User is not yet activated")); //tdb add list of pending activations
            return;
        }

        user.id=query.value(record.indexOf("id")).toInt();
        user.name=query.value(record.indexOf("name")).toString();
        user.description = query.value(record.indexOf("description")).toString();
        user.isActive=query.value(record.indexOf("is_active")).toBool();
        qDebug()<<user;
        emit(successfulLogin(user));
    }
    else{
        emit(badLogin("DB doesn't respond (tryLogIn function)"));
    }
}
