#include "netio.h"
#include "db.h"
#include "foodserver.h"


#include <QTcpSocket>
#include <QThread>
#include <QCoreApplication>
#include <QDebug>

FoodServer::FoodServer() {
    DataBaseHandler::initDataBase();
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

