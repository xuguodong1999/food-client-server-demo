#ifndef PRODUCT_H
#define PRODUCT_H

#include "config.h"
#include <QDataStream>
#include <QString>

class Product {
public:
    Product();

    friend QDataStream &operator>>(QDataStream &s, Product &product);

    friend QDataStream &operator<<(QDataStream &s, const Product &product);

private:
    int pid, uid, pstate;
    QString pname, pinfo, photo;
    double price;
public:
    int getPid() const;

    void setPid(int pid);

    int getUid() const;

    void setUid(int uid);

    int getPstate() const;

    void setPstate(Pstate pstate);

    const QString &getPname() const;

    void setPname(const QString &pname);

    const QString &getPinfo() const;

    void setPinfo(const QString &pinfo);

    const QString &getPhoto() const;

    void setPhoto(const QString &photo);

    double getPrice() const;

    void setPrice(double price);
};

#endif // PRODUCT_H
