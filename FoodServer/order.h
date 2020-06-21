#ifndef ORDER_H
#define ORDER_H

#include <QDataStream>
#include <QString>
#include "config.h"

// 订单类，对应于数据库订单表
class Order {
public:
    Order() {}

    friend QDataStream &operator>>(QDataStream &s, Order &o);

    friend QDataStream &operator<<(QDataStream &s, const Order &o);

public:
    int getOid() const {
        return oid;
    }

    void setOid(int oid) {
        Order::oid = oid;
    }

    int getUid() const {
        return uid;
    }

    void setUid(int uid) {
        Order::uid = uid;
    }

    int getPid() const {
        return pid;
    }

    void setPid(int pid) {
        Order::pid = pid;
    }

    int getOnum() const {
        return onum;
    }

    void setOnum(int onum) {
        Order::onum = onum;
    }

    double getOpay() const {
        return opay;
    }

    void setOpay(double opay) {
        Order::opay = opay;
    }

    const QString &getSubmittime() const {
        return submittime;
    }

    void setSubmittime(const QString &submittime) {
        Order::submittime = submittime;
    }

    int getOstate() const {
        return ostate;
    }

    void setOstate(Ostate ostate) {
        Order::ostate = ostate;
    }

protected:
    int oid, uid, pid, ostate, onum;
    double opay;
    QString submittime;

};

#include "product.h"
#include "user.h"

// 订单类的装饰，对应于用户界面订单表，增加价格、用户名、商品名、商品照片
class OrderWithFullInfo : public Order {
private:
    double price;
    QString uname, pname, photo;
public:
    OrderWithFullInfo() {}

    OrderWithFullInfo(const Order &order) {
        oid = order.getOid();
        uid = order.getUid();
        pid = order.getPid();
        ostate = order.getOstate();
        onum = order.getOnum();
        opay = order.getOpay();
        submittime = order.getSubmittime();
    }

    friend QDataStream &operator>>(QDataStream &s, OrderWithFullInfo &o);

    friend QDataStream &operator<<(QDataStream &s, const OrderWithFullInfo &o);

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
