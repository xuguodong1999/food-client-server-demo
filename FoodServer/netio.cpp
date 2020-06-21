#include "netio.h"
#include "user.h"
#include "product.h"
#include "order.h"
#include "db.h"
#include <QList>
#include <QHash>

NetIO::NetIO(QByteArray _buffer) : buffer(_buffer) {}

// 输入请求编号1、用户
// 输出回复编号1、状态、失败原因or完整用户信息
void NetIO::handle_userRegister(QDataStream &reader, QDataStream &writter) {
    User user;
    reader >> user;
    if (!UserDb::db_addUser(user)) {
        writter << taskid << false << "添加失败：用户名重复";
    } else {
        auto users = UserDb::db_getUser(user.getUname());
        if (users.isEmpty()) {
            writter << taskid << false << "查询失败：未知错误";
        } else {
            writter << taskid << true << users[0];
        }
    }
}

// 输入请求编号2、用户
// 输出回复编号2、状态、失败原因or完整用户信息
void NetIO::handle_userLogin(QDataStream &reader, QDataStream &writter) {
    User user;
    reader >> user;
    auto users = UserDb::db_getUser(user.getUname());
    if (users.isEmpty()) {
        writter << taskid << "用户名不存在";
    } else {
        if (users[0].getPassword() != user.getPassword()) {
            writter << taskid << false << "用户密码错误";
        } else if (UserDb::getUserClassification(users[0])
                   != UserDb::getUserClassification(user)) {
            writter << taskid << false << "用户类型错误";
        } else {
            writter << taskid << true << users[0];
        }
    }
}

// 输入请求编号3、商家id
// 输出回复编号3、状态、属于商家的所有产品
void NetIO::handle_sellerViewProduct(QDataStream &reader, QDataStream &writter) {
    int uid;
    reader >> uid;
    writter << taskid << true << ProductDb::db_getProduct4Seller(uid);
}

// 输入请求编号4、新产品
// 输出回复编号4、状态、属于商家的所有产品
void NetIO::handle_sellerAddProduct(QDataStream &reader, QDataStream &writter) {
    Product product;
    reader >> product;
    ProductDb::db_addProduct(product);
    int uid = product.getUid();
    writter << taskid << true << ProductDb::db_getProduct4Seller(uid);
}

// 输入请求编号5、修改后的产品
// 输出回复编号5、状态、属于商家的所有产品
void NetIO::handle_sellerChangeProduct(QDataStream &reader, QDataStream &writter) {
    Product product;
    reader >> product;
    ProductDb::db_delProduct(product.getPid());
    ProductDb::db_addProduct(product, true);
    int uid = product.getUid();
    writter << taskid << true << ProductDb::db_getProduct4Seller(uid);
}

// 输入请求编号6
// 输出回复编号6、状态、所有产品
void NetIO::handle_buyerViewProduct(QDataStream &reader, QDataStream &writter) {
    writter << taskid << true << ProductDb::db_getProduct();
}

// 输入请求编号7、订单
// 输出回复编号7、状态、促销信息
void NetIO::handle_buyerAddOrder(QDataStream &reader, QDataStream &writter) {
    qDebug() << "添加订单";
    Order order;
    User user;
    reader >> order >> user;
    OrderDb::db_addOrder(order);
    QString info;
    switch (Utype(user.getUtype())) {
        case vip1:
            info = "VIP1优惠: 使用1元红包进行结算抵扣。"
                   "提示：消费满￥500成为为VIP-2类用户，结算价格可打九五折。";
            break;
        case vip2:
            info = "VIP2优惠：结算价格打九五折。";
            break;
        default:
            info = "提示：消费满￥200成为为VIP-1类用户，"
                   "每笔订单使用1元红包进行结算抵扣；"
                   "消费满￥500成为为VIP-2类用户，结算价格可打九五折。";
    }
    writter << taskid << true << info;
}

// 输入请求编号8、商家id
// 输出回复编号8、状态、属于商家的订单
void NetIO::handle_sellerViewOrder(QDataStream &reader, QDataStream &writter) {
    int uid;
    reader >> uid;
    auto orders = OrderDb::db_getOrder4Seller(uid);
    auto fullOrders = OrderDb::getOrdersWithFullInfo(orders);
    writter << taskid << true << fullOrders;
}

// 输入请求编号9、订单
// 输出回复编号9、状态、属于商家的订单
void NetIO::handle_sellerChangeOrder(QDataStream &reader, QDataStream &writter) {
    OrderWithFullInfo order;
    reader >> order;

    OrderDb::db_delOrder(order.getOid());
    OrderDb::db_addOrder(order, true);

    // 在服务端补充订单表的信息
    auto p = ProductDb::db_getProduct(order.getPid());
    auto orders = OrderDb::db_getOrder(p[0].getUid());
    auto fullOrders = OrderDb::getOrdersWithFullInfo(orders);
    writter << taskid << true << fullOrders;
    //根据历史订单添加vip信息
    updateVip(order.getUid());
}

// 更新vip等级，输入订餐者id
void NetIO::updateVip(int uid) {
    double historyPay = 0;
    auto orders = OrderDb::db_getOrder(uid);
    for (auto &order:orders) {
        if (order.getOstate() == 2) {
            historyPay += order.getOpay();
        }
    }
    auto user = UserDb::db_getUser(uid)[0];
    int historyUtype = user.getUtype();
    if (historyPay >= 500) {
        user.setUtype(vip2);
    } else if (historyPay >= 200) {
        user.setUtype(vip1);
    }
    if (user.getUtype() != historyUtype) {
        UserDb::db_updateUserType(user);
    }
}

// 输入请求编号10、用户id
// 输出回复编号10、状态、属于用户的订单
void NetIO::handle_buyerViewOrder(QDataStream &reader, QDataStream &writter) {
    int uid;
    reader >> uid;
    auto orders = OrderDb::db_getOrder(uid);
    auto fullOrders = OrderDb::getOrdersWithFullInfo(orders);
    writter << taskid << true << fullOrders;
}

// 输入请求编号11、用户id
// 输出回复编号11、状态、属于用户的订单
void NetIO::handle_buyerChangeOrder(QDataStream &reader, QDataStream &writter) {
    qDebug() << "修改订餐者订单";
    OrderWithFullInfo order;
    User user;
    reader >> order >> user;
    OrderDb::db_delOrder(order.getOid());
    if (order.getOstate() != 4) {
        switch (Utype(user.getUtype())) {
            case vip1:
                user.setDiscount(std::make_shared<Vip1Discount>());
                break;
            case vip2:
                user.setDiscount(std::make_shared<Vip2Discount>());
                break;
            default:
                user.setDiscount(std::make_shared<Discount>());
        }
        double pay = user.pay(order.getPrice() * order.getOnum());
        qDebug() << "pay: " << pay;
        order.setOpay(pay);
        OrderDb::db_addOrder(order, true);
    }
    auto orders = OrderDb::db_getOrder(order.getUid());
    auto fullOrders = OrderDb::getOrdersWithFullInfo(orders);
    writter << taskid << true << fullOrders;
}

// 输入请求编号12
// 输出回复编号12、状态、字符串日志
void NetIO::handle_monthSalesCount(QDataStream &reader, QDataStream &writter) {
    auto result = OrderDb::db_getOrderDone();
    auto ret = OrderDb::getCountByMonth(result);
    QString info = "月销售额日志：\n";
    for (auto it = ret.cbegin(); it != ret.cend(); it++) {
        info.append(it.key());
        info.append(QString("销售额：￥%0\n").arg(it.value()));
    }
    writter << taskid << true << info;
}

// 输入请求编号13
// 输出回复编号13、状态、字符串日志
void NetIO::handle_weekSalesCount(QDataStream &reader, QDataStream &writter) {
    auto result = OrderDb::db_getOrderDone();
    auto ret = OrderDb::getCountByWeek(result);
    QString info = "周销售额日志：\n";
    for (auto it = ret.cbegin(); it != ret.cend(); it++) {
        info.append(it.key());
        info.append(QString("销售额：￥%0\n").arg(it.value()));
    }
    writter << taskid << true << info;
}

QByteArray NetIO::process() {
    QDataStream reader(&buffer, QIODevice::ReadOnly);
    reader >> taskid;
    QByteArray result;
    QDataStream writter(&result, QIODevice::WriteOnly);
    qint64 dataSize = 0;
    writter << dataSize;
    switch (taskid) {
        case 1: {//添加新用户
            handle_userRegister(reader, writter);
            break;
        }
        case 2: {
            handle_userLogin(reader, writter);
            break;
        }
        case 3: {
            handle_sellerViewProduct(reader, writter);
            break;
        }
        case 4: {
            handle_sellerAddProduct(reader, writter);
            break;
        }
        case 5: {
            handle_sellerChangeProduct(reader, writter);
            break;
        }
        case 6: {//订餐者查看推荐产品
            handle_buyerViewProduct(reader, writter);
            break;
        }
        case 7: {//订餐者添加订单
            handle_buyerAddOrder(reader, writter);
            break;
        }
        case 8: {//商家查看订单
            handle_sellerViewOrder(reader, writter);
            break;
        }
        case 9: {//商家修改订单
            handle_sellerChangeOrder(reader, writter);
            break;
        }
        case 10: {//用户查看订单
            handle_buyerViewOrder(reader, writter);
            break;
        }
        case 11: {//用户修改订单
            handle_buyerChangeOrder(reader, writter);
            break;
        }
        case 12: {//月销售额
            handle_monthSalesCount(reader, writter);
            break;
        }
        case 13: {//周销售额
            handle_weekSalesCount(reader, writter);
            break;
        }
        default:
            break;
    }
    dataSize = result.size();
    // 向buffer头写入buffer长度
    QDataStream _writter(&result, QIODevice::WriteOnly);
    _writter << dataSize;
    return result;
}