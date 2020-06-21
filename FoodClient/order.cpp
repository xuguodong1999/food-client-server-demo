#include "order.h"

QDataStream &operator<<(QDataStream &s, const Order &o) {
    s << o.oid << o.uid << o.pid << o.ostate << o.onum << o.opay << o.submittime;
    return s;
}

QDataStream &operator>>(QDataStream &s, Order &o) {
    s >> o.oid >> o.uid >> o.pid >> o.ostate >> o.onum >> o.opay >> o.submittime;
    return s;
}

QDataStream &operator<<(QDataStream &s, const OrderWithFullInfo &o) {
    s << o.oid << o.uid << o.pid << o.ostate << o.onum << o.opay << o.submittime
      << o.price << o.uname << o.pname << o.photo;
    return s;
}

QDataStream &operator>>(QDataStream &s, OrderWithFullInfo &o) {
    s >> o.oid >> o.uid >> o.pid >> o.ostate >> o.onum >> o.opay >> o.submittime
      >> o.price >> o.uname >> o.pname >> o.photo;;
    return s;
}