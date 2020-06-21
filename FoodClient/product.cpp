#include "product.h"

QDataStream &operator<<(QDataStream &s, const Product &product) {
    s << product.pid << product.uid << product.pstate
      << product.price << product.pname << product.pinfo << product.photo;
    return s;
}

QDataStream &operator>>(QDataStream &s, Product &product) {
    s >> product.pid >> product.uid >> product.pstate
      >> product.price >> product.pname >> product.pinfo >> product.photo;
    return s;
}