#ifndef ORDER_H
#define ORDER_H

#include <QDataStream>
#include <QString>
#include "config.h"

// 订单类，对应于数据库订单表
class Order {
public:
    Order();

    friend QDataStream &operator>>(QDataStream &s, Order &o);

    friend QDataStream &operator<<(QDataStream &s, const Order &o);

protected:
    int oid, uid, pid, ostate, onum;
    double opay;
    QString submittime;
public:
    int getOid() const;

    void setOid(int oid);

    int getUid() const;

    void setUid(int uid);

    int getPid() const;

    void setPid(int pid);

    int getOstate() const;

    void setOstate(Ostate ostate);

    int getOnum() const;

    void setOnum(int onum);

    double getOpay() const;

    void setOpay(double opay);

    const QString &getSubmittime() const;

    void setSubmittime(const QString &submittime);
};

#include "product.h"
#include "user.h"
// 订单类的装饰，对应于用户界面订单表，增加价格、用户名、商品名、商品照片
class OrderDecorator : public Order {
private:
    double price;
    QString uname, pname, photo;
public:
    OrderDecorator() {}

    OrderDecorator(const Order &order) {
        oid = order.getOid();
        uid = order.getUid();
        pid = order.getPid();
        ostate = order.getOstate();
        onum = order.getOnum();
        opay = order.getOpay();
        submittime = order.getSubmittime();
    }

    friend QDataStream &operator>>(QDataStream &s, OrderDecorator &o);

    friend QDataStream &operator<<(QDataStream &s, const OrderDecorator &o);

    void setProduct(const Product &product) {
        pname = product.getPname();
        photo = product.getPhoto();
        price = product.getPrice();
    }

    void setUser(const User &user) {
        uname = user.getUname();
    }

    const QString &getUname() const {
        return uname;
    }

    const QString &getPname() const {
        return pname;
    }

    const QString &getPhoto() const {
        return photo;
    }

    double getPrice() const {
        return price;
    }
};

#endif // ORDER_H
