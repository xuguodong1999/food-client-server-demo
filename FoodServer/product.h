#ifndef PRODUCT_H
#define PRODUCT_H

#include "config.h"
#include <QDataStream>
#include <QString>

class Product {
public:
    Product() {}

    friend QDataStream &operator>>(QDataStream &s, Product &product);

    friend QDataStream &operator<<(QDataStream &s, const Product &product);

    int getPid() const {
        return pid;
    }

    void setPid(int pid) {
        Product::pid = pid;
    }

    int getUid() const {
        return uid;
    }

    void setUid(int uid) {
        Product::uid = uid;
    }

    const QString &getPname() const {
        return pname;
    }

    void setPname(const QString &pname) {
        Product::pname = pname;
    }

    const QString &getPinfo() const {
        return pinfo;
    }

    void setPinfo(const QString &pinfo) {
        Product::pinfo = pinfo;
    }

    const QString &getPhoto() const {
        return photo;
    }

    void setPhoto(const QString &photo) {
        Product::photo = photo;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        Product::price = price;
    }

    int getPstate() const {
        return pstate;
    }

    void setPstate(Pstate pstate) {
        Product::pstate = pstate;
    }

private:
    int pid, uid, pstate;
    QString pname, pinfo, photo;
    double price;
};

#endif // PRODUCT_H
