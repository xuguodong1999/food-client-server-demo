#ifndef NETIO_H
#define NETIO_H

#include <QDataStream>
#include <QByteArray>

// 网络通信
// 网络流读写类，根据简单的协议处理请求
class ServerNetService {
    int taskid;
public:
    ServerNetService(QByteArray _buffer);

    // 输入请求编号1、用户
    // 输出回复编号1、状态、失败原因or完整用户信息
    void userRegister(QDataStream &reader, QDataStream &writter);

    // 输入请求编号2、用户
    // 输出回复编号2、状态、失败原因or完整用户信息
    void userLogin(QDataStream &reader, QDataStream &writter);

    // 输入请求编号3、商家id
    // 输出回复编号3、状态、属于商家的所有产品
    void sellerViewProduct(QDataStream &reader, QDataStream &writter);

    // 输入请求编号4、新产品
    // 输出回复编号4、状态、属于商家的所有产品
    void sellerAddProduct(QDataStream &reader, QDataStream &writter);

    // 输入请求编号5、修改后的产品
    // 输出回复编号5、状态、属于商家的所有产品
    void sellerChangeProduct(QDataStream &reader, QDataStream &writter);

    // 输入请求编号6
    // 输出回复编号6、状态、所有产品
    void buyerViewProduct(QDataStream &reader, QDataStream &writter);

    // 输入请求编号7、订单
    // 输出回复编号7、状态、促销信息
    void buyerAddOrder(QDataStream &reader, QDataStream &writter);

    // 输入请求编号8、商家id
    // 输出回复编号8、状态、属于商家的订单
    void sellerViewOrder(QDataStream &reader, QDataStream &writter);

    // 输入请求编号9、订单
    // 输出回复编号9、状态、属于商家的订单
    void sellerChangeOrder(QDataStream &reader, QDataStream &writter);

    // 更新vip等级，输入订餐者id
    void updateVip(int uid);

    // 输入请求编号10、用户id
    // 输出回复编号10、状态、属于用户的订单
    void buyerViewOrder(QDataStream &reader, QDataStream &writter);

    // 输入请求编号11、用户id
    // 输出回复编号11、状态、属于用户的订单
    void buyerChangeOrder(QDataStream &reader, QDataStream &writter);

    // 输入请求编号12
    // 输出回复编号12、状态、字符串日志
    void monthSalesCount(QDataStream &reader, QDataStream &writter);

    // 输入请求编号13
    // 输出回复编号13、状态、字符串日志
    void weekSalesCount(QDataStream &reader, QDataStream &writter);

    QByteArray process();

private:
    QByteArray buffer;
};

#endif //NETIO_H