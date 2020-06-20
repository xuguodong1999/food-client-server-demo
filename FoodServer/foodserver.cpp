#include "foodserver.h"
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QThread>
#include <QCoreApplication>
#include "user.h"
#include "order.h"
#include "product.h"
#include <iostream>

using namespace std;

inline int getUserType(const User &user) {
    switch (user.getUtype()) {
        case 0:
            return 0;
        case 2:
            return 2;
        default:
            return 1;
    }
}

const auto USER_SQL = QString(R"(
    create table UserTable(uid integer primary key autoincrement, utype integer, uname varchar, password varchar, photo varchar)
    )");

const auto ORDER_SQL = QString(R"(
    create table OrderTable(oid integer primary key autoincrement, uid integer, pid integer, ostate integer, onum integer, opay double,  submittime varchar)
    )");

const auto PRODUCT_SQL = QString(R"(
    create table ProductTable(pid integer primary key autoincrement, uid integer, pstate integer, price double, pname varchar, pinfo varchar, photo varchar)
    )");

FoodServer::FoodServer() {
    initDataBase();
    server = new QTcpServer();
    QHostAddress addr = QHostAddress::LocalHost;
    int port = 5001;
    while (!server->listen(addr, port)) {
        qDebug() << "fail to connect to " << addr << " in port " << port;
        QThread::msleep(1000);
    }
    connect(server, &QTcpServer::newConnection, [=]() {
        if (server->hasPendingConnections()) {
            auto socket = server->nextPendingConnection();
            connect(socket, &QTcpSocket::readyRead, [=]() {
                // 处理网络流
                auto binaryData = socket->readAll();
                int taskid;
                QDataStream reader(&binaryData, QIODevice::ReadOnly);
                reader >> taskid;
                qDebug() << "收到请求id：" << taskid;
                QByteArray result;
                QDataStream writter(&result, QIODevice::WriteOnly);
                qint64 dataSize = 0;
                writter << dataSize;
                switch (taskid) {
                    case 1: {//添加新用户
                        User user;
                        reader >> user;
                        if (!addUser(user)) {
                            writter << taskid << false;
                        } else {
                            auto users = getUser(user.getUname());
                            if (users.isEmpty()) {
                                writter << taskid << false;
                            } else {
                                writter << taskid << true << users[0];
                            }
                        }
                        break;
                    }
                    case 2: {//用户登录
                        User user;
                        reader >> user;
                        auto users = getUser(user.getUname());
                        if (users.isEmpty()) {
                            writter << taskid << false;
                        } else {
                            if (users[0].getPassword() != user.getPassword()
                                || getUserType(users[0]) != getUserType(user)) {
                                writter << taskid << false;
                            } else {
                                writter << taskid << true << users[0];
                            }
                        }
                        break;
                    }
                    case 3: {//卖家查看自己的产品
                        int uid;
                        reader >> uid;
                        auto p = getProductByUid(uid);
                        writter << taskid << true << p;
                        qDebug() << "发送前：" << p.size() << "件产品-bits:" << result.size();
                        break;
                    }
                    case 4: {
                        qDebug() << "添加产品";
                        Product product;
                        reader >> product;
                        int uid = product.getUid();
                        addProduct(product);
                        auto p = getProductByUid(uid);
                        writter << taskid << true << p;
                        break;
                    }
                    case 5: {
                        qDebug() << "修改产品";
                        Product product;
                        reader >> product;
                        deleteProduct(product.getPid());
                        addProduct(product, true);
                        auto p = getProductByUid(product.getUid());
                        writter << taskid << true << p;
                        break;
                    }
                    case 6: {//订餐者查看推荐产品
                        auto p = getProduct();
                        writter << taskid << true << p;
                        qDebug() << "发送前：" << p.size() << "件产品-bits:" << result.size();
                        break;
                    }
                    case 7: {//订餐者添加订单
                        qDebug() << "添加订单";
                        Order o;
                        reader >> o;
                        addOrder(o);
                        writter << taskid << true;
                        break;
                    }
                    case 8: {//商家查看订单
                        int uid;
                        reader >> uid;
                        auto orders = getOrder4Seller(uid);
                        qDebug() << "商家订单数：" << orders.size();
                        QList<OrderAdapter> ordersInfo;
                        for (auto &o:orders) {
                            auto p = getProductByPid(o.getPid());
                            auto u = getUser(o.getUid());
                            OrderAdapter oi(o);
                            oi.setProduct(p[0]);
                            oi.setUser(u[0]);
                            ordersInfo.push_back(oi);
                        }
                        writter << taskid << true << ordersInfo;
                        break;
                    }
                    case 9: {//商家修改订单
                        qDebug() << "修改商家订单";
                        OrderAdapter order;
                        reader >> order;
                        deleteOrder(order.getOid());
                        addOrder(order, true);
                        auto p = getProductByPid(order.getPid());
                        auto orders = getOrder4Seller(p[0].getUid());
                        qDebug() << "商家订单数：" << orders.size();
                        QList<OrderAdapter> ordersInfo;
                        for (auto &o:orders) {
                            auto p = getProductByPid(o.getPid());
                            auto u = getUser(o.getUid());
                            OrderAdapter oi(o);
                            oi.setProduct(p[0]);
                            oi.setUser(u[0]);
                            ordersInfo.push_back(oi);
                        }
                        writter << taskid << true << ordersInfo;
                        break;
                    }
                    case 10: {//用户查看订单
                        int uid;
                        reader >> uid;
                        auto orders = getOrder(uid);
                        QList<OrderAdapter> ordersInfo;
                        for (auto &o:orders) {
                            auto p = getProductByPid(o.getPid());
                            auto u = getUser(o.getUid());
                            OrderAdapter oi(o);
                            oi.setProduct(p[0]);
                            oi.setUser(u[0]);
                            ordersInfo.push_back(oi);
                        }
                        writter << taskid << true << ordersInfo;
                        break;
                    }
                    case 11: {//用户修改订单
                        qDebug() << "修改订餐者订单";
                        OrderAdapter order;
                        reader >> order;
                        deleteOrder(order.getOid());
                        if (order.getOstate() != 4)
                            addOrder(order, true);
                        auto orders = getOrder(order.getUid());
                        QList<OrderAdapter> ordersInfo;
                        for (auto &o:orders) {
                            auto p = getProductByPid(o.getPid());
                            auto u = getUser(o.getUid());
                            OrderAdapter oi(o);
                            oi.setProduct(p[0]);
                            oi.setUser(u[0]);
                            ordersInfo.push_back(oi);
                        }
                        writter << taskid << true << ordersInfo;
                        break;
                    }
                    case 12: {//月销售额
                        writter << taskid << true << QString("月销售额日志");
                        break;
                    }
                    case 13: {//周销售额
                        writter << taskid << true << QString("周销售额日志");
                        break;
                    }
                    default:
                        break;
                }
                dataSize = result.size();
                QDataStream writter2(&result, QIODevice::WriteOnly);
                writter2 << dataSize;
                socket->write(result);
            });
            connect(socket, &QTcpSocket::disconnected, [=]() {
                socket->close();
                socket->deleteLater();
            });
        }
    });
}

FoodServer::~FoodServer() {
    delete server;
}

FoodServer &FoodServer::getInstance() {
    static FoodServer instance;
    return instance;
}

QSqlError FoodServer::initDataBase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qApp->applicationDirPath() + "/food.db");
    if (!db.open())
        return db.lastError();
    QSqlQuery q;
    QStringList tables = db.tables();
    if (!tables.contains("UserTable", Qt::CaseInsensitive)) {
        if (!q.exec(USER_SQL)) return q.lastError();
//        User user;
//        user.setPhoto("default");
//        user.setPassword("123456");
//        user.setUname("沙县小吃");
//        user.setUtype(0);
//        addUser(user);

    }
    if (!tables.contains("OrderTable", Qt::CaseInsensitive)) {
        if (!q.exec(ORDER_SQL)) return q.lastError();
//        Order order;
//        order.setOpay(101);
//        order.setPid(1);
//        order.setOnum(10);
//        order.setOstate(0);
//        order.setUid(1);
//        order.setSubmittime("");
//        addOrder(order);
    }
    if (!tables.contains("ProductTable", Qt::CaseInsensitive)) {
        if (!q.exec(PRODUCT_SQL)) return q.lastError();
//        Product product;
//        product.setUid(1);
//        product.setPhoto("dafault");
//        product.setPrice(11);
//        product.setPname("茶树菇排骨汤");
//        product.setPinfo("一种很少很贵的汤");
//        product.setPstate(0);
//        addProduct(product);
    }
    return QSqlError();
}

bool FoodServer::addUser(const User &user) {
    if (!getUser(user.getUname()).isEmpty()) {
        return false;//不允许用户名重复
    }
    QSqlQuery q;
    q.exec(QString(R"(insert into UserTable(utype, uname, password, photo) values(%1, "%2", "%3", "%4"))")
                   .arg(user.getUtype()).arg(user.getUname())
                   .arg(user.getPassword()).arg(user.getPhoto())
    );
    return true;
}

void FoodServer::addProduct(const Product &product, bool putId) {
    QSqlQuery q;
    if (putId) {
        q.exec(
                QString(R"(
    insert into ProductTable(pid, uid, pstate, price, pname, pinfo, photo) values(%0, %1,%2,%3,"%4","%5","%6")
    )").arg(product.getPid()).arg(product.getUid()).arg(product.getPstate())
                        .arg(product.getPrice()).arg(product.getPname()).arg(product.getPinfo()).arg(
                                product.getPhoto()));
    } else
        q.exec(
                QString(R"(
    insert into ProductTable(uid, pstate, price, pname, pinfo, photo) values(%1,%2,%3,"%4","%5","%6")
    )").arg(product.getUid()).arg(product.getPstate())
                        .arg(product.getPrice()).arg(product.getPname()).arg(product.getPinfo()).arg(product.getPhoto())
        );
}

void FoodServer::addOrder(const Order &order, bool putId) {
    QSqlQuery q;
    if (putId) {
        q.exec(
                QString(R"(
    insert into OrderTable(oid, uid, pid, ostate, onum, opay, submittime) values(%0,%1,%2,%3,%4,%5,"%6")
    )").arg(order.getOid()).arg(order.getUid()).arg(order.getPid())
                        .arg(order.getOstate()).arg(order.getOnum()).arg(order.getOpay()).arg(order.getSubmittime()));
    } else
        q.exec(
                QString(R"(
    insert into OrderTable(uid, pid, ostate, onum, opay, submittime) values(%1,%2,%3,%4,%5,"%6")
    )").arg(order.getUid()).arg(order.getPid())
                        .arg(order.getOstate()).arg(order.getOnum()).arg(order.getOpay()).arg(order.getSubmittime())
        );
}

QList<User> FoodServer::getUser(const QString &username) {
    QSqlQuery q;
    q.exec(QString(R"(select * from UserTable where uname="%1")").arg(username));
    QList<User> users;
    while (q.next()) {
        User user;
        user.setUid(q.value(0).toInt());
        user.setUtype(q.value(1).toInt());
        user.setUname(q.value(2).toString());
        user.setPassword(q.value(3).toString());
        user.setPhoto(q.value(4).toString());
        users.push_back(user);
    }
    return users;
}

QList<User> FoodServer::getUser(const int uid) {
    QSqlQuery q;
    q.exec(QString(R"(select * from UserTable where uid=%1)").arg(uid));
    QList<User> users;
    while (q.next()) {
        User user;
        user.setUid(q.value(0).toInt());
        user.setUtype(q.value(1).toInt());
        user.setUname(q.value(2).toString());
        user.setPassword(q.value(3).toString());
        user.setPhoto(q.value(4).toString());
        users.push_back(user);
    }
    return users;
}

void FoodServer::deleteProduct(const int pid) {
    QSqlQuery q;
    q.exec(QString(R"(delete from ProductTable where pid=%1)").arg(pid));
}

QList<Product> FoodServer::getProduct() {
    QSqlQuery q;
    q.exec("select * from ProductTable");
    QList<Product> products;
    while (q.next()) {
        Product product;
        product.setPid(q.value(0).toInt());
        product.setUid(q.value(1).toInt());
        product.setPstate(q.value(2).toInt());
        product.setPrice(q.value(3).toDouble());
        product.setPname(q.value(4).toString());
        product.setPinfo(q.value(5).toString());
        product.setPhoto(q.value(6).toString());
        products.push_back(product);
    }
    return products;
}

QList<Product> FoodServer::getProductByUid(const int uid) {
    QSqlQuery q;
    q.exec(QString("select * from ProductTable where uid=%1").arg(uid));
    qDebug() << q.lastQuery() << q.lastError();
    QList<Product> products;
    while (q.next()) {
        Product product;
        product.setPid(q.value(0).toInt());
        product.setUid(q.value(1).toInt());
        product.setPstate(q.value(2).toInt());
        product.setPrice(q.value(3).toDouble());
        product.setPname(q.value(4).toString());
        product.setPinfo(q.value(5).toString());
        product.setPhoto(q.value(6).toString());
        products.push_back(product);
    }
    qDebug() << "检索出：" << products.size() << "件产品";
    return products;
}

void FoodServer::deleteOrder(const int oid) {
    QSqlQuery q;
    q.exec(QString(R"(delete from OrderTable where oid=%1)").arg(oid));
}

QList<Order> FoodServer::getOrder(const int uid) {
    QSqlQuery q;
    q.exec(QString("select * from OrderTable where uid=%1").arg(uid));
    qDebug() << q.lastQuery() << q.lastError();
    QList<Order> orders;
    while (q.next()) {
        Order order;
        order.setOid(q.value(0).toInt());
        order.setUid(q.value(1).toInt());
        order.setPid(q.value(2).toInt());
        order.setOstate(q.value(3).toInt());
        order.setOnum(q.value(4).toInt());
        order.setOpay(q.value(5).toDouble());
        order.setSubmittime(q.value(6).toString());
        orders.push_back(order);
    }
    return orders;
}

QList<Order> FoodServer::getOrder4Seller(const int uid) {
    QSqlQuery q;
    q.exec(QString(
            "select o.* from UserTable, OrderTable o, ProductTable where UserTable.uid=%1 and ProductTable.uid=UserTable.uid and ProductTable.pid=o.pid and o.ostate!=0 and o.ostate!=4").arg(
            uid));
    qDebug() << q.lastQuery() << q.lastError();
    QList<Order> orders;
    while (q.next()) {
        Order order;
        order.setOid(q.value(0).toInt());
        order.setUid(q.value(1).toInt());
        order.setPid(q.value(2).toInt());
        order.setOstate(q.value(3).toInt());
        order.setOnum(q.value(4).toInt());
        order.setOpay(q.value(5).toDouble());
        order.setSubmittime(q.value(6).toString());
        orders.push_back(order);
    }
    return orders;
}

QList<Product> FoodServer::getProductByPid(const int pid) {
    QSqlQuery q;
    q.exec(QString("select * from ProductTable where pid=%1").arg(pid));
    qDebug() << q.lastQuery() << q.lastError();
    QList<Product> products;
    while (q.next()) {
        Product product;
        product.setPid(q.value(0).toInt());
        product.setUid(q.value(1).toInt());
        product.setPstate(q.value(2).toInt());
        product.setPrice(q.value(3).toDouble());
        product.setPname(q.value(4).toString());
        product.setPinfo(q.value(5).toString());
        product.setPhoto(q.value(6).toString());
        products.push_back(product);
    }
    qDebug() << "检索出：" << products.size() << "件产品";
    return products;
}
