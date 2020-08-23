#ifndef CONFIG_H
#define CONFIG_H
enum Utype {
    seller = 0,
    buyer = 1,
    admin = 2,
    vip1 = 3,
    vip2 = 4
};
enum Pstate {
    onsell = 0,
    notsell = 1
};
enum Ostate {
    incart = 0,
    submit = 1,
    done = 2,
    sellerReject = 3,
    userDelete = 4
};

enum TaskId {
    USER_REGISTER = 1,
    USER_LOGIN = 2,
    SELLER_VIEW_PRODUCT = 3,
    SELLER_ADD_PRODUCT = 4,
    SELLER_CHANGE_PRODUCT = 5,
    BUYER_VIEW_PRODUCT = 6,
    BUYER_ADD_ORDER = 7,
    SELLER_VIEW_ORDER = 8,
    SELLER_CHANGE_ORDER = 9,
    USER_VIEW_ORDER = 10,
    USER_CHANGE_ORDER = 11,
    COUNT_MONTH_SALE = 12,
    COUNT_WEEK_SALE = 13
};
#endif // CONFIG_H
