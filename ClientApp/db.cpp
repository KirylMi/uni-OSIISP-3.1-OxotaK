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

}

void DB::tryLogIn(User user)
{
    //.....check DB, update user if everything is OK.
    if (1==1)
        emit(successfulLogin(user));
    else
        emit(badLogin(QString()));
}
