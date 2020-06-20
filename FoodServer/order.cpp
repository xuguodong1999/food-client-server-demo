#include "order.h"


using namespace std;

Order::Order() {

}

int Order::getOid() const {
    return oid;
}

void Order::setOid(int oid) {
    Order::oid = oid;
}

int Order::getUid() const {
    return uid;
}

void Order::setUid(int uid) {
    Order::uid = uid;
}

int Order::getPid() const {
    return pid;
}

void Order::setPid(int pid) {
    Order::pid = pid;
}

int Order::getOstate() const {
    return ostate;
}

void Order::setOstate(Ostate ostate) {
    Order::ostate = ostate;
}

int Order::getOnum() const {
    return onum;
}

void Order::setOnum(int onum) {
    Order::onum = onum;
}

double Order::getOpay() const {
    return opay;
}

void Order::setOpay(double opay) {
    Order::opay = opay;
}

const QString &Order::getSubmittime() const {
    return submittime;
}

void Order::setSubmittime(const QString &submittime) {
    Order::submittime = submittime;
}

QDataStream &operator<<(QDataStream &s, const Order &o) {
    s << o.oid << o.uid << o.pid << o.ostate << o.onum << o.opay << o.submittime;
    return s;
}

QDataStream &operator>>(QDataStream &s, Order &o) {
    s >> o.oid >> o.uid >> o.pid >> o.ostate >> o.onum >> o.opay >> o.submittime;
    return s;
}

QDataStream &operator<<(QDataStream &s, const OrderDecorator &o) {
    s << o.oid << o.uid << o.pid << o.ostate << o.onum << o.opay << o.submittime
      << o.price << o.uname << o.pname << o.photo;
    return s;
}

QDataStream &operator>>(QDataStream &s, OrderDecorator &o) {
    s >> o.oid >> o.uid >> o.pid >> o.ostate >> o.onum >> o.opay >> o.submittime
      >> o.price >> o.uname >> o.pname >> o.photo;;
    return s;
}