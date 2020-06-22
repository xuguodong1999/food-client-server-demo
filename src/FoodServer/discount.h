#ifndef DISCOUNT_H
#define DISCOUNT_H

class Discount {
public:
    Discount() {}

    virtual double calculate(double price) { return price; }
};

class Vip1Discount : public Discount {
public:
    Vip1Discount() {}

    double calculate(double price) override {
        return price - 1;
    }
};

class Vip2Discount : public Discount {
public:
    Vip2Discount() {}

    double calculate(double price) override {
        return price * 0.95;
    }

};

#endif // DISCOUNT_H
