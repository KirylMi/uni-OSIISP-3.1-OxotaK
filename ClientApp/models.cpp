#include "models.h"

QDebug operator<<(QDebug debug, const User &user)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << '{' << "id: " <<user.id << ", \nname:" << user.name << ", \nusername:" << user.username
                    <<", \npassword:"<<user.password<<", \ndescription:"<<user.description<<", \nis_active:"<<user.isActive<<'}';
    return debug;
}
