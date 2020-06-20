#include "discount.h"

Discount::Discount() {

}

double Discount::calculate(double price) {
    return price;
}

Vip1Discount::Vip1Discount() {

}

double Vip1Discount::calculate(double price) {
    return price - 1;
}

Vip2Discount::Vip2Discount() {

}

double Vip2Discount::calculate(double price) {
    return price * 0.95;
}
