#ifndef FOODSERVER_H
#define FOODSERVER_H

#include <QTcpServer>

// 服务器类，单例模式
class FoodServer : public QObject {
Q_OBJECT
public:

    ~FoodServer();

    static FoodServer &getInstance();

    FoodServer(const FoodServer &) = delete;

    FoodServer &operator=(const FoodServer &) = delete;

private:
    FoodServer();

    QTcpServer *server;


};

#endif // FOODSERVER_H
