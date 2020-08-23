#ifndef USER_H
#define USER_H

#include "config.h"
#include <QString>
#include <QDataStream>
#include "discount.h"
#include <memory>

class User {
public:
    User() {}

    friend QDataStream &operator>>(QDataStream &s, User &user);

    friend QDataStream &operator<<(QDataStream &s, const User &user);

    int getUid() const {
        return uid;
    }

    double pay(double _pay) {
        return discount->calculate(_pay);
    }

    void setDiscount(std::shared_ptr<Discount> _discount) {
        discount = _discount;
    }

    int getUtype() const {
        return utype;
    }

    void setUtype(Utype utype) {
        User::utype = utype;
    }

    void setUid(int uid) {
        User::uid = uid;
    }

    const QString &getUname() const {
        return uname;
    }

    void setUname(const QString &uname) {
        User::uname = uname;
    }

    const QString &getPassword() const {
        return password;
    }

    void setPassword(const QString &password) {
        User::password = password;
    }

    const QString &getPhoto() const {
        return photo;
    }

    void setPhoto(const QString &photo) {
        User::photo = photo;
    }

private:
    int uid, utype;
    QString uname, password, photo;
    std::shared_ptr<Discount> discount;
};

#endif // USER_H
