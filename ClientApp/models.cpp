#include "models.h"

QDebug operator<<(QDebug debug, const User &user)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << '{' << "id: " <<user.id << ", \nname:" << user.name << ", \nusername:" << user.username
                    <<", \npassword:"<<user.password<<", \ndescription:"<<user.description<<", \nis_active:"<<user.isActive<<'}';
    return debug;
}

QString getDrinkTypeString(drinkType drinkType){
    switch (drinkType){
    case Soda:
        return "Soda";
    case Beer:
        return "Beer";
    case Vodka:
        return "Vodka";
    case UNDEFINED:
        return "UNDEFINED";
    default:
        return "UNDEFINED";
    }
}

drinkType getDrinkTypeFromString(QString str){
    if (str=="Soda") return Soda;
    if (str=="Beer") return Beer;
    if (str=="Vodka") return Vodka;
    return UNDEFINED;
}

bool Drink::operator <(const Drink &other) const
{
    return this->id<other.id;
}
