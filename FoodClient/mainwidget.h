#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDataStream>
#include "userform.h"
#include "usertodoform.h"
#include "viewwidget.h"
#include "productform.h"
#include "orderform.h"
class MainWidget : public QWidget {
Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

    ~MainWidget();

signals:
public slots:

    void s_register();//发送注册信息

    void s_login();//发送登录信息
    void s_sellerProductView();
    void s_sellerOrderView();
    void s_buyerProductView();
    void s_buyerOrderView();
private:
    void popSellerProductView(QList<Product>&products);
    void popBuyerProductView(QList<Product>&products);

    void popSellerOrderView(QList<OrderWithFullInfo>&orders);
    void popBuyerOrderView(QList<OrderWithFullInfo>&orders);

    // 订单和产品的函数需要知道被操作的表单，在connect的时候修改当前表单指针的指向
    void s_addProduct();//发送卖家产品添加信息

    void s_changeProduct();//发送卖家修改添加信息

    void s_addOrder();//发送订餐者订单信息

    void s_sellerHandleOrder(bool accept=true);//修改订餐者订单信息
    void s_buyerHandleOrder(bool accept=true);
private:
    bool isConnected;
    QTcpSocket *socket;
    QByteArray binaryData;
    qint64 dataSize;
    void query(const QByteArray &binaryData);

    User user;
    UserForm *userform;
    ViewWidget *view;
    UserTodoForm *userTodoForm;

    ProductForm*currentProductForm;
    OrderForm*currentOrderForm;
};

#endif // MAINWIDGET_H
