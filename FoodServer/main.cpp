#include <QCoreApplication>
#include "foodserver.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    auto &server = FoodServer::getInstance();
    return a.exec();
}
