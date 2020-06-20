#ifndef FOODSERVER_H
#define FOODSERVER_H

#include <QTcpServer>
#include <QList>
#include <QtSql>
#include "user.h"
#include "product.h"
#include "order.h"
class FoodServer:public QObject{
    Q_OBJECT
public:
    ~FoodServer();
    FoodServer(const FoodServer&)=delete;
    FoodServer&operator=(const FoodServer&)=delete;
    static FoodServer&getInstance();
private:
    FoodServer();
    QTcpServer*server;
    QSqlError initDataBase();


    bool addUser(const User&user);
    QList<User> getUser(const QString&username);
    QList<User> getUser(const int uid);

    void addProduct(const Product&product,bool putId=false);
    void deleteProduct(const int pid);
    QList<Product> getProduct();//所有产品
    QList<Product> getProductByUid(const int uid);//一个商家的所有产品
    QList<Product> getProductByPid(const int pid);

    void addOrder(const Order&order,bool putId=false);
    void deleteOrder(const int oid);
    QList<Order> getOrder(const int uid);//一个用户的所有订单
    QList<Order> getOrder4Seller(const int uid);//一个商户的所有订单
};

#endif // FOODSERVER_H
