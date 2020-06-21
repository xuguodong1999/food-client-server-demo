#include "db.h"

using namespace std;

QList<User> UserDb::db_getUser(const QString &username) {
    auto db = DbHandlerFactory::getDbHandler("UserTable");
    db->queryByString("select", "uname", username);
    return UserDb::queryUsers(db->exec());
}

QList<User> UserDb::db_getUser(const int uid) {
    auto db = DbHandlerFactory::getDbHandler("UserTable");
    db->queryByInt("select", "uid", uid);
    return UserDb::queryUsers(db->exec());
}

void ProductDb::db_delProduct(const int pid) {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryByInt("delete", "pid", pid);
    db->exec();//不需要处理返回值
}

QList<Product> ProductDb::db_getProduct() {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryAll("select");
    return ProductDb::queryProducts(db->exec());
}

QList<Product> ProductDb::db_getProduct4Seller(const int uid) {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryByInt("select", "uid", uid);
    return ProductDb::queryProducts(db->exec());
}

void OrderDb::db_delOrder(const int oid) {
    auto db = DbHandlerFactory::getDbHandler("OrderTable");
    db->queryByInt("delete", "oid", oid);
    db->exec();//不需要处理返回值
}

QList<Order> OrderDb::db_getOrder(const int uid) {
    auto db = DbHandlerFactory::getDbHandler("OrderTable");
    db->queryByInt("select", "uid", uid);
    return OrderDb::queryOrders(db->exec());
}

QList<Product> ProductDb::db_getProduct(const int pid) {
    auto db = DbHandlerFactory::getDbHandler("ProductTable");
    db->queryByInt("select", "pid", pid);
    return ProductDb::queryProducts(db->exec());
}

QList<Order> OrderDb::db_getOrderDone() {
    auto db = DbHandlerFactory::getDbHandler("OrderTable");
    db->queryByInt("select", "ostate", Ostate::done);
    return OrderDb::queryOrders(db->exec());
}

QHash<QString, double> OrderDb::getCountByMonth(const QList<Order> &orders) {
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

QHash<QString, double> OrderDb::getCountByWeek(const QList<Order> &orders) {
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

void UserDb::db_updateUserType(const User &user) {
    QSqlQuery q;
    q.exec(QString(R"(update UserTable set utype=%0 where uid=%1)")
                   .arg(user.getUtype()).arg(user.getUid())
    );
    qDebug() << q.lastQuery() << q.lastError();
}

bool UserDb::db_addUser(const User &user) {
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

void ProductDb::db_addProduct(const Product &product, bool putId) {
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

void OrderDb::db_addOrder(const Order &order, bool putId) {
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

QList<Order> OrderDb::db_getOrder4Seller(const int uid) {
    //跨表查询
    auto db = DbHandlerFactory::getDbHandler("");
    auto query = QString("select o.* from UserTable, OrderTable o, ProductTable "
                         "where UserTable.uid=%1 and "
                         "ProductTable.uid=UserTable.uid and "
                         "ProductTable.pid=o.pid and "
                         "o.ostate!=%2 and o.ostate!=%3"
    ).arg(uid).arg(Ostate::incart).arg(Ostate::userDelete);
    return OrderDb::queryOrders(db->exec(query));
}

QList<OrderWithFullInfo> OrderDb::getOrdersWithFullInfo(const QList<Order> orders) {
    QList<OrderWithFullInfo> result;
    for (auto &o:orders) {
        auto p = ProductDb::db_getProduct(o.getPid());
        auto u = UserDb::db_getUser(o.getUid());
        OrderWithFullInfo oi(o);
        oi.setProduct(p[0]);
        oi.setUser(u[0]);
        result.push_back(oi);
    }
    return result;
}

QSqlError DataBaseHandler::initDataBase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qApp->applicationDirPath() + "/food.db");
    if (!db.open())
        return db.lastError();
    QSqlQuery q;
    QStringList tables = db.tables();
    const QString CREATE_USER = QString(R"(
    create table UserTable(uid integer primary key autoincrement, utype integer, uname varchar, password varchar, photo varchar)
    )");

    const QString CREATE_ORDER = QString(R"(
    create table OrderTable(oid integer primary key autoincrement, uid integer, pid integer, ostate integer, onum integer, opay double,  submittime varchar)
    )");

    const QString CREATE_PRODUCT = QString(R"(
    create table ProductTable(pid integer primary key autoincrement, uid integer, pstate integer, price double, pname varchar, pinfo varchar, photo varchar)
    )");

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
