#include "user.h"

QDataStream &operator<<(QDataStream &s, const User &user) {
    s << user.uid << user.utype << user.uname << user.password << user.photo;
    return s;
}

QDataStream &operator>>(QDataStream &s, User &user) {
    s >> user.uid >> user.utype >> user.uname >> user.password >> user.photo;
    return s;
}