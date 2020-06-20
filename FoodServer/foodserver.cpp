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


FoodServer::FoodServer() {
    initDataBase();
    server = new QTcpServer();
    QHostAddress addr = QHostAddress::LocalHost;
    int port = 5001;
    while (!server->listen(addr, port)) {
        qDebug() << "未能连接到 " << addr << " 的 " << port << " 端口";
        QThread::msleep(1000);
    }
    connect(server, &QTcpServer::newConnection, [=]() {
        if (server->hasPendingConnections()) {
            auto socket = server->nextPendingConnection();
            connect(socket, &QTcpSocket::readyRead, [=]() {
                // 处理网络流
                NetIO netio(socket->readAll());
                socket->write(netio.process());
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
        if (!q.exec(CREATE_USER)) return q.lastError();
    }
    if (!tables.contains("OrderTable", Qt::CaseInsensitive)) {
        if (!q.exec(CREATE_ORDER)) return q.lastError();
    }
    if (!tables.contains("ProductTable", Qt::CaseInsensitive)) {
        if (!q.exec(CREATE_PRODUCT)) return q.lastError();
    }
    return QSqlError();
}

QList<User> FoodServer::db_getUser(const QString &username) {
    auto db = DbHandlerFactory::getDbHandler("UserTable");
    db->queryByString("select", "uname", username);
    return UserDbHandler::queryUsers(db->exec());
}

QList<User> FoodServer::db_getUser(const int uid) {
    auto db = DbHandlerFactory::getDbHandler("UserTable");
    db->queryByInt("select", "uid", uid);
    return UserDbHandler::queryUsers(db->exec());
}

void FoodServer::db_delProduct(const int pid) {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryByInt("delete", "pid", pid);
    db->exec();//不需要处理返回值
}

QList<Product> FoodServer::db_getProduct() {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryAll("select");
    return ProductDbHandler::queryProducts(db->exec());
}

QList<Product> FoodServer::db_getProduct4Seller(const int uid) {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryByInt("select", "uid", uid);
    return ProductDbHandler::queryProducts(db->exec());
}

void FoodServer::db_delOrder(const int oid) {
    auto db = DbHandlerFactory::getDbHandler("OrderTable");
    db->queryByInt("delete", "oid", oid);
    db->exec();//不需要处理返回值
}

QList<Order> FoodServer::db_getOrder(const int uid) {
    auto db = DbHandlerFactory::getDbHandler("OrderTable");
    db->queryByInt("select", "uid", uid);
    return OrderDbHandler::queryOrders(db->exec());
}

QList<Product> FoodServer::db_getProduct(const int pid) {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryByInt("select", "pid", pid);
    return ProductDbHandler::queryProducts(db->exec());
}

QList<Order> FoodServer::db_getOrderDone() {
    auto db = DbHandlerFactory::getDbHandler("OrderTable");
    db->queryByInt("select", "ostate", Ostate::done);
    return OrderDbHandler::queryOrders(db->exec());
}

QHash<QString, double> FoodServer::getCountByMonth(const QList<Order> &orders) {
    QHash<QString, double> count;
    for (auto &r:orders) {
        auto split = r.getSubmittime().split(" ");// 日期示例：周六 6月 20 09:31:45 2020
        if (count.find(split[1]) == count.end()) {
            count[split[1]] = r.getOpay();
        } else {
            count[split[1]] += r.getOpay();
        }
    }
    return count;
}

QHash<QString, double> FoodServer::getCountByWeek(const QList<Order> &orders) {
    QHash<QString, double> count;
    for (auto &r:orders) {
        auto split = r.getSubmittime().split(" ");// 日期示例：周六 6月 20 09:31:45 2020
        if (count.find(split[0]) == count.end()) {
            count[split[0]] = r.getOpay();
        } else {
            count[split[0]] += r.getOpay();
        }
    }
    return count;
}

void FoodServer::db_updateUserType(const User &user) {
    QSqlQuery q;
    q.exec(QString(R"(update UserTable set utype=%0 where uid=%1)")
                   .arg(user.getUtype()).arg(user.getUid())
    );
    qDebug() << q.lastQuery() << q.lastError();
}

bool FoodServer::db_addUser(const User &user) {
    if (!db_getUser(user.getUname()).isEmpty()) {
        return false;//不允许用户名重复
    }
    auto db = DbHandlerFactory::getDbHandler("");
    auto query = QString(R"(insert into UserTable(utype, uname, password, photo) values(%1, "%2", "%3", "%4"))")
            .arg(user.getUtype()).arg(user.getUname())
            .arg(user.getPassword()).arg(user.getPhoto());
    db->exec(query);
    return true;
}

void FoodServer::db_addProduct(const Product &product, bool putId) {
    auto db = DbHandlerFactory::getDbHandler("");
    QString query;
    if (putId) {
        query = QString(
                R"(insert into ProductTable(pid, uid, pstate, price, pname, pinfo, photo) values(%0, %1,%2,%3,"%4","%5","%6"))").arg(
                product.getPid()).arg(product.getUid()).arg(product.getPstate()).arg(product.getPrice()).arg(
                product.getPname()).arg(product.getPinfo()).arg(product.getPhoto());
    } else {
        query = QString(
                R"(insert into ProductTable(uid, pstate, price, pname, pinfo, photo) values(%1,%2,%3,"%4","%5","%6"))").arg(
                product.getUid()).arg(product.getPstate()).arg(product.getPrice()).arg(product.getPname()).arg(
                product.getPinfo()).arg(product.getPhoto());
    }
    db->exec(query);
}

void FoodServer::db_addOrder(const Order &order, bool putId) {
    auto db = DbHandlerFactory::getDbHandler("");
    QString query;
    if (putId) {
        query = QString(
                R"(insert into OrderTable(oid, uid, pid, ostate, onum, opay, submittime) values(%0,%1,%2,%3,%4,%5,"%6"))").arg(
                order.getOid()).arg(order.getUid()).arg(order.getPid()).arg(order.getOstate()).arg(order.getOnum()).arg(
                order.getOpay()).arg(order.getSubmittime());
    } else {
        query = QString(
                R"(insert into OrderTable(uid, pid, ostate, onum, opay, submittime) values(%1,%2,%3,%4,%5,"%6"))").arg(
                order.getUid()).arg(order.getPid()).arg(order.getOstate()).arg(order.getOnum()).arg(
                order.getOpay()).arg(order.getSubmittime());
    }
    db->exec(query);
}

QList<Order> FoodServer::db_getOrder4Seller(const int uid) {
    //跨表查询
    auto db = DbHandlerFactory::getDbHandler("");
    auto query = QString("select o.* from UserTable, OrderTable o, ProductTable "
                         "where UserTable.uid=%1 and "
                         "ProductTable.uid=UserTable.uid and "
                         "ProductTable.pid=o.pid and "
                         "o.ostate!=%2 and o.ostate!=%3"
    ).arg(uid).arg(Ostate::incart).arg(Ostate::userDelete);
    return OrderDbHandler::queryOrders(db->exec(query));
}
