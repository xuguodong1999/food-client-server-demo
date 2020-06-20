#include "product.h"

using namespace std;

Product::Product() {

}

int Product::getPid() const {
    return pid;
}

void Product::setPid(int pid) {
    Product::pid = pid;
}

int Product::getUid() const {
    return uid;
}

void Product::setUid(int uid) {
    Product::uid = uid;
}

int Product::getPstate() const {
    return pstate;
}

void Product::setPstate(Pstate pstate) {
    Product::pstate = pstate;
}

const QString &Product::getPname() const {
    return pname;
}

void Product::setPname(const QString &pname) {
    Product::pname = pname;
}

const QString &Product::getPinfo() const {
    return pinfo;
}

void Product::setPinfo(const QString &pinfo) {
    Product::pinfo = pinfo;
}

const QString &Product::getPhoto() const {
    return photo;
}

void Product::setPhoto(const QString &photo) {
    Product::photo = photo;
}

double Product::getPrice() const {
    return price;
}

void Product::setPrice(double price) {
    Product::price = price;
}

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