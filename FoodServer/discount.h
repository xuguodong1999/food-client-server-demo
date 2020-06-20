#ifndef DISCOUNT_H
#define DISCOUNT_H


class Discount {
public:
    Discount();

    virtual double calculate(double price);
};

class Vip1Discount : public Discount {
public:
    Vip1Discount();

    double calculate(double price) override;
};

class Vip2Discount : public Discount {
public:
    Vip2Discount();

    double calculate(double price) override;
};

#endif // DISCOUNT_H
