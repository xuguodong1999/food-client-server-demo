#ifndef FOODSERVER_H
#define FOODSERVER_H

#include "user.h"
#include "product.h"
#include "order.h"
#include <QList>
#include <QtSql>
#include <QHash>
#include <QTcpServer>
#include <memory>

// 数据库表的基类，用于简化代码
class DataBaseHandler {
public:
    // 适用与select、delete的单条件查询
    void queryByInt(const QString &action, const QString &idName, int value) {
        query = (action + " * from " + tableName + " where " + idName + "=%1").arg(value);
    }

    // 适用与select、delete的单条件查询
    void queryByString(const QString &action, const QString &idName, const QString &value) {
        query = (action + " * from " + tableName + " where " + idName + "=\"%1\"").arg(value);
    }

    // 适用与select、delete的单条件查询
    void queryAll(const QString &action) {
        query = action + " * from " + tableName;
    }

    // 执行语句
    QSqlQuery &exec() {
        q.exec(query);
        error = q.lastError().text();
        if (logging) {
            qDebug() << getQuery() << "\n" << getError();
        }
        return q;
    }

    // 执行任意一个陌生语句
    QSqlQuery &exec(const QString &_query) {
        query = _query;
        return exec();
    }

    const QString &getQuery() const {
        return query;
    }

    const QString &getError() const {
        return error;
    }

    void setLogging(bool logging) {
        DataBaseHandler::logging = logging;
    }

protected:
    void setTableName(const QString &_name) { tableName = _name; }

private:
    QString query, error, tableName;
    QSqlQuery q;
    bool logging;
};

class UserDbHandler : public DataBaseHandler {
public:
    UserDbHandler() { setTableName("UserTable"); }

    static QString getUserClassification(const User &user) {
        QString utype;
        switch (Utype(user.getUtype())) {
            case seller:
                utype = "商家";
                break;
            case admin:
                utype = "管理员";
                break;
            case buyer:
            case vip1:
            case vip2:
                utype = "订餐者";
                break;
        }
        return utype;
    }

    static QList<User> queryUsers(QSqlQuery &q) {
        QList<User> users;
        while (q.next()) {
            User user;
            user.setUid(q.value(0).toInt());
            user.setUtype(Utype(q.value(1).toInt()));
            user.setUname(q.value(2).toString());
            user.setPassword(q.value(3).toString());
            user.setPhoto(q.value(4).toString());
            users.push_back(user);
        }
        return users;
    }
};

class ProductDbHandler : public DataBaseHandler {
public:
    ProductDbHandler() { setTableName("ProductTable"); }

    static inline QList<Product> queryProducts(QSqlQuery &q) {
        QList<Product> products;
        while (q.next()) {
            Product product;
            product.setPid(q.value(0).toInt());
            product.setUid(q.value(1).toInt());
            product.setPstate(Pstate(q.value(2).toInt()));
            product.setPrice(q.value(3).toDouble());
            product.setPname(q.value(4).toString());
            product.setPinfo(q.value(5).toString());
            product.setPhoto(q.value(6).toString());
            products.push_back(product);
        }
        return products;
    }

};

class OrderDbHandler : public DataBaseHandler {
public:
    OrderDbHandler() { setTableName("OrderTable"); }

    static QList<Order> queryOrders(QSqlQuery &q) {
        QList<Order> orders;
        while (q.next()) {
            Order order;
            order.setOid(q.value(0).toInt());
            order.setUid(q.value(1).toInt());
            order.setPid(q.value(2).toInt());
            order.setOstate(Ostate(q.value(3).toInt()));
            order.setOnum(q.value(4).toInt());
            order.setOpay(q.value(5).toDouble());
            order.setSubmittime(q.value(6).toString());
            orders.push_back(order);
        }
        return orders;
    }
};

class DbHandlerFactory {
public:
    static std::shared_ptr<DataBaseHandler> getDbHandler(const QString &tableName, bool logging = false) {
        std::shared_ptr<DataBaseHandler> dbHandler;
        if (tableName == "UserTable") {
            dbHandler = std::make_shared<UserDbHandler>();
        } else if (tableName == "ProductTable") {
            dbHandler = std::make_shared<ProductDbHandler>();
        } else if (tableName == "OrderTable") {
            dbHandler = std::make_shared<OrderDbHandler>();
        } else {
            dbHandler = std::make_shared<DataBaseHandler>();
        }
        dbHandler->setLogging(logging);
        return dbHandler;
    }
};


// 服务器类，单例模式
class FoodServer : public QObject {
Q_OBJECT
public:

    ~FoodServer();

    static FoodServer &getInstance();

    FoodServer(const FoodServer &) = delete;

    FoodServer &operator=(const FoodServer &) = delete;

private:
    const QString CREATE_USER = QString(R"(
    create table UserTable(uid integer primary key autoincrement, utype integer, uname varchar, password varchar, photo varchar)
    )");

    const QString CREATE_ORDER = QString(R"(
    create table OrderTable(oid integer primary key autoincrement, uid integer, pid integer, ostate integer, onum integer, opay double,  submittime varchar)
    )");

    const QString CREATE_PRODUCT = QString(R"(
    create table ProductTable(pid integer primary key autoincrement, uid integer, pstate integer, price double, pname varchar, pinfo varchar, photo varchar)
    )");

    FoodServer();

    QTcpServer *server;

    QSqlError initDataBase();

private://数据库操作
    static bool db_addUser(const User &user);

    static void db_updateUserType(const User &user);

    static QList<User> db_getUser(const int uid);

    static QList<User> db_getUser(const QString &username);

    static void db_addProduct(const Product &product, bool putId = false);

    static void db_delProduct(const int pid);

    static QList<Product> db_getProduct();//所有产品
    static QList<Product> db_getProduct(const int pid);//指定编号的产品
    static QList<Product> db_getProduct4Seller(const int uid);//一个商家的所有产品

    static void db_addOrder(const Order &order, bool putId = false);

    static void db_delOrder(const int oid);

    static QList<Order> db_getOrder(const int uid);//一个订餐者的所有订单
    static QList<Order> db_getOrderDone();//所有完成交易的订单
    static QList<Order> db_getOrder4Seller(const int uid);//一个商家的所有订单
    static QHash<QString, double> getCountByMonth(const QList<Order> &orders);//按月算销售额
    static QHash<QString, double> getCountByWeek(const QList<Order> &orders);//按周算销售额
    //网络通信
    // 网络流读写类，根据简单的协议处理请求
    class NetIO {
        int taskid;
    public:
        NetIO(QByteArray _buffer) : buffer(_buffer) {}

        // 输入请求编号1、用户
        // 输出回复编号1、状态、失败原因or完整用户信息
        void handle_userRegister(QDataStream &reader, QDataStream &writter) {
            User user;
            reader >> user;
            if (!db_addUser(user)) {
                writter << taskid << false << "添加失败：用户名重复";
            } else {
                auto users = db_getUser(user.getUname());
                if (users.isEmpty()) {
                    writter << taskid << false << "查询失败：未知错误";
                } else {
                    writter << taskid << true << users[0];
                }
            }
        }

        // 输入请求编号2、用户
        // 输出回复编号2、状态、失败原因or完整用户信息
        void handle_userLogin(QDataStream &reader, QDataStream &writter) {
            User user;
            reader >> user;
            auto users = db_getUser(user.getUname());
            if (users.isEmpty()) {
                writter << taskid << "用户名不存在";
            } else {
                if (users[0].getPassword() != user.getPassword()) {
                    writter << taskid << false << "用户密码错误";
                } else if (UserDbHandler::getUserClassification(users[0])
                           != UserDbHandler::getUserClassification(user)) {
                    writter << taskid << false << "用户类型错误";
                } else {
                    writter << taskid << true << users[0];
                }
            }
        }

        // 输入请求编号3、商家id
        // 输出回复编号3、状态、属于商家的所有产品
        void handle_sellerViewProduct(QDataStream &reader, QDataStream &writter) {
            int uid;
            reader >> uid;
            writter << taskid << true << db_getProduct4Seller(uid);
        }
        // 输入请求编号4、新产品
        // 输出回复编号4、状态、属于商家的所有产品
        void handle_sellerAddProduct(QDataStream &reader, QDataStream &writter) {
            Product product;
            reader >> product;
            db_addProduct(product);
            int uid = product.getUid();
            writter << taskid << true << db_getProduct4Seller(uid);
        }
        // 输入请求编号5、修改后的产品
        // 输出回复编号5、状态、属于商家的所有产品
        void handle_sellerChangeProduct(QDataStream &reader, QDataStream &writter) {
            Product product;
            reader >> product;
            db_delProduct(product.getPid());
            db_addProduct(product, true);
            int uid = product.getUid();
            writter << taskid << true << db_getProduct4Seller(uid);
        }
        // 输入请求编号6
        // 输出回复编号6、状态、所有产品
        void handle_buyerViewProduct(QDataStream &reader, QDataStream &writter) {
            writter << taskid << true <<db_getProduct();
        }
        // 输入请求编号7、订单
        // 输出回复编号7、状态、促销信息
        void handle_buyerAddOrder(QDataStream &reader, QDataStream &writter) {
            qDebug() << "添加订单";
            Order order;
            User user;
            reader >> order>>user;
            db_addOrder(order);
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
        void handle_sellerViewOrder(QDataStream &reader, QDataStream &writter) {
            int uid;
            reader >> uid;
            auto orders = db_getOrder4Seller(uid);
            // 在服务端补充订单表的信息
            QList<OrderDecorator> ordersInfo;
            for (auto &o:orders) {
                auto p = db_getProduct(o.getPid());
                auto u = db_getUser(o.getUid());
                OrderDecorator oi(o);
                oi.setProduct(p[0]);
                oi.setUser(u[0]);
                ordersInfo.push_back(oi);
            }
            writter << taskid << true << ordersInfo;
        }
        // 输入请求编号9、订单
        // 输出回复编号9、状态、属于商家的订单
        void handle_sellerChangeOrder(QDataStream &reader, QDataStream &writter) {
            OrderDecorator order;
            reader >> order;

            db_delOrder(order.getOid());
            db_addOrder(order, true);

            // 在服务端补充订单表的信息
            auto p = db_getProduct(order.getPid());
            auto orders = db_getOrder4Seller(p[0].getUid());
            QList<OrderDecorator> ordersInfo;
            for (auto &o:orders) {
                auto p = db_getProduct(o.getPid());
                auto u = db_getUser(o.getUid());
                OrderDecorator oi(o);
                oi.setProduct(p[0]);
                oi.setUser(u[0]);
                ordersInfo.push_back(oi);
            }
            writter << taskid << true << ordersInfo;
            //根据历史订单添加vip信息
            updateVip(order.getUid());
        }

        // 更新vip等级，输入订餐者id
        void updateVip(int uid){
            double historyPay = 0;
            auto orders = db_getOrder(uid);
            for (auto &order:orders) {
                if (order.getOstate() == 2) {
                    historyPay += order.getOpay();
                }
            }
            auto user = db_getUser(uid)[0];
            int historyUtype = user.getUtype();
            if (historyPay >= 500) {
                user.setUtype(vip2);
            } else if (historyPay >= 200) {
                user.setUtype(vip1);
            }
            if (user.getUtype() != historyUtype) {
                db_updateUserType(user);
            }
        }

        // 输入请求编号10、用户id
        // 输出回复编号10、状态、属于用户的订单
        void handle_buyerViewOrder(QDataStream &reader, QDataStream &writter) {
            int uid;
            reader >> uid;
            auto orders = db_getOrder(uid);
            QList<OrderDecorator> ordersInfo;
            for (auto &o:orders) {
                auto p = db_getProduct(o.getPid());
                auto u = db_getUser(o.getUid());
                OrderDecorator oi(o);
                oi.setProduct(p[0]);
                oi.setUser(u[0]);
                ordersInfo.push_back(oi);
            }
            writter << taskid << true << ordersInfo;
        }

        // 输入请求编号11、用户id
        // 输出回复编号11、状态、属于用户的订单
        void handle_buyerChangeOrder(QDataStream &reader, QDataStream &writter) {
            qDebug() << "修改订餐者订单";
            OrderDecorator order;
            User user;
            reader >> order >> user;
            db_delOrder(order.getOid());
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
                db_addOrder(order, true);
            }
            auto orders = db_getOrder(order.getUid());
            QList<OrderDecorator> ordersInfo;
            for (auto &o:orders) {
                auto p = db_getProduct(o.getPid());
                auto u = db_getUser(o.getUid());
                OrderDecorator oi(o);
                oi.setProduct(p[0]);
                oi.setUser(u[0]);
                ordersInfo.push_back(oi);
            }
            writter << taskid << true << ordersInfo;
        }

        QByteArray process() {
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
                    handle_sellerAddProduct(reader,writter);
                    break;
                }
                case 5: {
                    handle_sellerChangeProduct(reader,writter);
                    break;
                }
                case 6: {//订餐者查看推荐产品
                    handle_buyerViewProduct(reader,writter);
                    break;
                }
                case 7: {//订餐者添加订单
                    handle_buyerAddOrder(reader,writter);
                    break;
                }
                case 8: {//商家查看订单
                    handle_sellerViewOrder(reader,writter);
                    break;
                }
                case 9: {//商家修改订单
                    handle_sellerChangeOrder(reader,writter);
                    break;
                }
                case 10: {//用户查看订单
                    handle_buyerViewOrder(reader,writter);
                    break;
                }
                case 11: {//用户修改订单
                    handle_buyerChangeOrder(reader,writter);
                    break;
                }
                case 12: {//月销售额
                    auto result = db_getOrderDone();
                    auto ret = getCountByMonth(result);
                    QString info = "月销售额日志：\n";
                    for (auto it = ret.cbegin(); it != ret.cend(); it++) {
                        info.append(it.key());
                        info.append(QString("销售额：￥%0\n").arg(it.value()));
                    }
                    writter << taskid << true << info;
                    break;
                }
                case 13: {//周销售额
                    auto result = db_getOrderDone();
                    auto ret = getCountByWeek(result);
                    QString info = "周销售额日志：\n";
                    for (auto it = ret.cbegin(); it != ret.cend(); it++) {
                        info.append(it.key());
                        info.append(QString("销售额：￥%0\n").arg(it.value()));
                    }
                    writter << taskid << true << info;
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

    private:
        QByteArray buffer;
    };
};

#endif // FOODSERVER_H
