#include "user.h"


using namespace std;

User::User() {

}

int User::getUid() const {
    return uid;
}

void User::setUid(int uid) {
    User::uid = uid;
}

int User::getUtype() const {
    return utype;
}

void User::setUtype(int utype) {
    User::utype = utype;
}

const QString &User::getUname() const {
    return uname;
}

void User::setUname(const QString &uname) {
    User::uname = uname;
}

const QString &User::getPassword() const {
    return password;
}

void User::setPassword(const QString &password) {
    User::password = password;
}

const QString &User::getPhoto() const {
    return photo;
}

void User::setPhoto(const QString &photo) {
    User::photo = photo;
}


QDataStream &operator<<(QDataStream &s, const User &user) {
    s << user.uid << user.utype << user.uname << user.password << user.photo;
    return s;
}

QDataStream &operator>>(QDataStream &s, User &user) {
    s >> user.uid >> user.utype >> user.uname >> user.password >> user.photo;
    return s;
}