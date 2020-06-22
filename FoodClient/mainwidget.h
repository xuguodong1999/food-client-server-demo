#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>
#include "userform.h"
#include "todoform.h"
#include "viewwidget.h"
#include "productform.h"
#include "orderform.h"

class MainWidget : public QWidget {
Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

    ~MainWidget();
    // ******************************
    // 网络通信部分
private:
    User user;
    bool isConnected;
    QTcpSocket *socket;
    qint64 toReceiveBufferSize;
    QByteArray toAppendBuffer;
    const QHostAddress addr = QHostAddress::LocalHost;
    const int port = 5001;

    // 发送数据
    void send(const QByteArray &binaryData);

    // 根据协议分发指令
    void process(TaskId taskid, QDataStream &reader);

    // 在lambda表达式里调用的网络请求
    // 订单和产品的函数需要知道被操作的表单地址
    // 在进入请求函数之前，借助信号的发送者指针，修改当前表单指针的指向
    void requestSellerAddProduct();//发送商家产品添加信息

    void requestSellerChangeProduct();//发送商家修改添加信息

    void requestUserAddOrder();//发送订餐者订单信息

    void requestSellerChangeOrder(bool accept = true);//修改订餐者订单信息
    void requestBuyerChangeOrder(bool accept = true);

private slots:

    // 直接作为槽函数发送的网络请求
    void requestSellerProductView();

    void requestSellerOrderView();

    void requestBuyerProductView();

    void requestBuyerOrderView();

    void requestMonthSaleCount();

    void requestWeekSaleCount();
    // ******************************
    // GUI部分
private:
    void popWarning(const QString &info);

    void popUserTodoForm(const User &user);

    void popSellerProductView(QList<Product> &products);

    void popBuyerProductView(QList<Product> &products);

    void popSellerOrderView(QList<OrderWithFullInfo> &orders);

    void popBuyerOrderView(QList<OrderWithFullInfo> &orders);

    void popBuyerAddOrderMessage();

    void popBuyerGotoOrderViewMessage(const QString &info);

    void popBuyerSubmitOrderMessage();

    void popBuyerCancelOrderMessage();

    void popSellerAcceptOrderMessage();

    void popSellerCancelOrderMessage();

private slots:

    void popSellerRefreshProductMessage();

private:
    void updateView();

    void closeView();

    void closeProductForm();

    UserForm *userform;
    TodoForm *userTodoForm;
    ViewWidget *view;
    ProductForm *currentProductForm;
    OrderForm *currentOrderForm;
};

#endif // MAINWIDGET_H
