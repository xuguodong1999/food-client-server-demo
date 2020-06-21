#ifndef DB_H
#define DB_H

#include "user.h"
#include "product.h"
#include "order.h"
#include <QList>
#include <QtSql>
#include <QHash>
#include <memory>


// 数据库表操作的基类，用于简化代码
class DataBaseHandler {
public:
    static QSqlError initDataBase();

    // 准备适用与select、delete的单条件查询
    void queryByInt(const QString &action, const QString &idName, int value) {
        query = (action + " * from " + tableName + " where " + idName + "=%1").arg(value);
    }

    // 准备适用与select、delete的单条件查询
    void queryByString(const QString &action, const QString &idName, const QString &value) {
        query = (action + " * from " + tableName + " where " + idName + "=\"%1\"").arg(value);
    }

    // 准备适用与select、delete的单条件查询
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
};

class ProductDbHandler : public DataBaseHandler {
public:
    ProductDbHandler() { setTableName("ProductTable"); }

};

class OrderDbHandler : public DataBaseHandler {
public:
    OrderDbHandler() { setTableName("OrderTable"); }
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

// 以静态成员函数的方式封装一系列数据库顶层操作
class UserDb {
public:
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

    static bool db_addUser(const User &user);

    static void db_updateUserType(const User &user);

    static QList<User> db_getUser(const int uid);

    static QList<User> db_getUser(const QString &username);
};

class ProductDb {
public:
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

    static void db_addProduct(const Product &product, bool putId = false);

    static void db_delProduct(const int pid);

    static QList<Product> db_getProduct();//所有产品
    static QList<Product> db_getProduct(const int pid);//指定编号的产品
    static QList<Product> db_getProduct4Seller(const int uid);//一个商家的所有产品
};

class OrderDb {
public:
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

    static void db_addOrder(const Order &order, bool putId = false);

    static void db_delOrder(const int oid);

    static QList<Order> db_getOrder(const int uid);//一个订餐者的所有订单
    static QList<Order> db_getOrderDone();//所有完成交易的订单
    static QList<Order> db_getOrder4Seller(const int uid);//一个商家的所有订单
    static QHash<QString, double> getCountByMonth(const QList<Order> &orders);//按月算销售额
    static QHash<QString, double> getCountByWeek(const QList<Order> &orders);//按周算销售额
    static QList<OrderWithFullInfo> getOrdersWithFullInfo(const QList<Order> orders);
};

#endif //DB_H