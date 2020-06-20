#include <QCoreApplication>
#include "foodserver.h"
#include <QDebug>
#include <QDataStream>
#include <QList>


int main(int argc, char *argv[]) {
    qApp->setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication a(argc, argv);
    auto &server = FoodServer::getInstance();
    return a.exec();
}
