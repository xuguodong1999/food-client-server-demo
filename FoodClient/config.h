#ifndef CONFIG_H
#define CONFIG_H
#include <QSize>
inline const QSize getSubWindowSize(){
    return QSize(880,220);
}
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
enum Service {
    new_user,

};
#endif // CONFIG_H
