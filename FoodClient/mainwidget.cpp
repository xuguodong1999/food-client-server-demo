#include "mainwidget.h"
#include <QHostAddress>
#include <QDebug>
#include "user.h"
#include "order.h"
#include "product.h"
#include <QToolButton>
#include <QGridLayout>
#include "orderform.h"
#include "productform.h"
#include <QMessageBox>
#include <QDateTime>
#include <QPlainTextEdit>

#define safeDelete(w) \
    w->close();\
    w->deleteLater();\
    w = nullptr;


MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent), isConnected(false), userform(nullptr), view(nullptr),
        userTodoForm(nullptr), currentProductForm(nullptr), currentOrderForm(nullptr) {
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    userform = new UserForm(this);
    socket = new QTcpSocket();
    socket->abort();
    QHostAddress addr = QHostAddress::LocalHost;
    int port = 5001;
    socket->connectToHost(addr, port);
    connect(socket, &QTcpSocket::connected, [=]() { isConnected = true; });
    connect(socket, &QTcpSocket::disconnected, [=]() {
        isConnected = false;
        safeDelete(socket);
    });
    connect(userform->getRegister(), &QToolButton::clicked, this, &MainWidget::s_register);
    connect(userform->getLogin(), &QToolButton::clicked, this, &MainWidget::s_login);
    connect(socket, &QTcpSocket::readyRead, [=]() {
        // 处理网络流
        // socket->readAll()函数只读一个tcp包
        // qt会把一次较大的socket->write分成若干个小包发过来
        // 没有提供一次读完的接口，这些包还会乱序。。。
        QDataStream reader0(&binaryData, QIODevice::ReadOnly);
        auto tmp = socket->readAll();
        if (binaryData.isEmpty()) {
            binaryData.append(tmp);
            reader0 >> dataSize;
            qDebug() << "标识长度：" << dataSize;
            qDebug() << "当前长度：" << binaryData.length();
            if (binaryData.size() < dataSize) {
                return;
            }
        } else {
            binaryData.append(tmp);
            qDebug() << "当前长度：" << binaryData.length();
            if (binaryData.size() < dataSize) {
                qDebug() << "继续读取...";
                return;
            }
        }
        QDataStream reader(&binaryData, QIODevice::ReadOnly);
        reader >> dataSize;
//        auto binaryData = socket->readAll();
        int taskid;
        reader >> taskid;
        QByteArray result;
        QDataStream writter(&result, QIODevice::WriteOnly);
        switch (taskid) {
            case 1:
            case 2: {//收到添加新用户的回复
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "登录失败";
                    QMessageBox::information(
                            nullptr,
                            "提示",
                            "登陆失败",
                            QMessageBox::Yes
                    );
                } else {
                    reader >> user;
                    // 跳转功能界面
                    userform->update(user);
                    qDebug() << user.getUname() << "登录成功";
                    UserTodoBuilder *builder;
                    TodoFormController controller;
                    qDebug() << user.getUtype();
                    switch (user.getUtype()) {
                        case 0:
                            builder = new SellerTodoBuilder();
                            userTodoForm = controller.createUserTodoForm(builder, user);
                            connect(userTodoForm->getBtn1(), &QToolButton::clicked, this,
                                    &MainWidget::s_sellerProductView);
                            connect(userTodoForm->getBtn2(), &QToolButton::clicked, this,
                                    &MainWidget::s_sellerOrderView);
                            break;
                        case 2:
                            builder = new AdminTodoBuilder();
                            userTodoForm = controller.createUserTodoForm(builder, user);
                            // 管理员
                            connect(userTodoForm->getBtn1(), &QToolButton::clicked, [=]() {
                                //发一条信息查询月销售额
                                QByteArray binaryData;
                                QDataStream writer(&binaryData, QIODevice::WriteOnly);
                                writer << 12;
                                query(binaryData);
                            });
                            connect(userTodoForm->getBtn2(), &QToolButton::clicked, [=]() {
                                //发一条信息查询周销售额
                                QByteArray binaryData;
                                QDataStream writer(&binaryData, QIODevice::WriteOnly);
                                writer << 13;
                                query(binaryData);
                            });
                            break;
                        case 1:
                        case 3:
                        case 4:
                            builder = new BuyerTodoBuilder();
                            userTodoForm = controller.createUserTodoForm(builder, user);
                            connect(userTodoForm->getBtn1(), &QToolButton::clicked, this,
                                    &MainWidget::s_buyerProductView);
                            connect(userTodoForm->getBtn2(), &QToolButton::clicked, this,
                                    &MainWidget::s_buyerOrderView);
                    }
                    userTodoForm->setParent(this);
                    userform->close();
                    userTodoForm->show();
                }
                break;
            }
            case 3 : {// 收到卖家产品数据
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "查询失败";
                } else {
                    qDebug() << "处理卖家产品数据";
                    QList<Product> products;
                    reader >> products;
                    qDebug() << "接收到：" << products.size() << "件产品-" << binaryData.size();
                    popSellerProductView(products);
                }
                break;
            }
            case 4: {//添加产品
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "添加失败";
                } else {
                    safeDelete(currentProductForm);
                    qDebug() << "添加成功";
                    QList<Product> products;
                    reader >> products;
                    popSellerProductView(products);
                }
                break;
            }
            case 5: {//修改产品
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "修改失败";
                } else {
                    qDebug() << "修改成功";
                    QList<Product> products;
                    reader >> products;
                    popSellerProductView(products);
                }
                break;
            }
            case 6: {// 收到订餐者推荐产品
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "查询失败";
                } else {
                    qDebug() << "处理订餐者推荐产品数据";
                    QList<Product> products;
                    reader >> products;
                    qDebug() << "接收到：" << products.size() << "件产品-" << binaryData.size();
                    popBuyerProductView(products);
                }
                break;
            }
            case 7: {
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "添加购物车失败";
                } else {
                    QString info;
                    reader >>  info;
                    QMessageBox::StandardButton result = QMessageBox::information(
                            nullptr,
                            "成功添加到购物车",
                            info + "去购物车结算吗",
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::No
                    );
                    switch (result) {
                        case QMessageBox::Yes:
                        safeDelete(view);
                            s_buyerOrderView();
//                            view->getBackBtn()->click();
                            break;
                        case QMessageBox::No:
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            case 8:
            case 9: {//刷新商家订单
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "查询失败";
                } else {
                    qDebug() << "处理卖家订单";
                    QList<OrderAdapter> orders;
                    reader >> orders;
                    popSellerOrderView(orders);
                }
                break;
            }
            case 10:
            case 11: {//刷新用户订单
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "查询失败";
                } else {
                    qDebug() << "处理订餐者订单";
                    QList<OrderAdapter> orders;
                    reader >> orders;
                    popBuyerOrderView(orders);
                }
                break;
            }
            case 12:
            case 13: {
                bool success;
                reader >> success;
                if (!success) {
                    qDebug() << "查询失败";
                } else {
                    QWidget *w = new QWidget();
                    w->resize(size());
                    QPlainTextEdit *edit = new QPlainTextEdit();
                    auto l = new QGridLayout();
                    l->addWidget(edit);
                    w->setLayout(l);
                    QString text;
                    reader >> text;
                    edit->setFocusPolicy(Qt::NoFocus);
                    edit->setPlainText(text);
                    w->show();
                }
                break;
            }
            default:
                break;
        }
        qDebug() << "清空缓存";
        binaryData = QByteArray();
    });
}

MainWidget::~MainWidget() {

}

void MainWidget::query(const QByteArray &binaryData) {
    if (!isConnected) {
        qDebug() << "连接服务器失败";
        return;
    }
    socket->write(binaryData);
}

void MainWidget::s_register() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    writer << 1 << userform->getUser();//提交注册信息
    query(binaryData);
}

void MainWidget::s_login() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    writer << 2 << userform->getUser();//提交登录信息
    query(binaryData);
}

void MainWidget::s_sellerProductView() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    writer << 3 << user.getUid();//提交卖家身份
    query(binaryData);
}

void MainWidget::s_sellerOrderView() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    writer << 8 << user.getUid();
    query(binaryData);
}

void MainWidget::s_buyerProductView() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    writer << 6;
    query(binaryData);
}

void MainWidget::s_buyerOrderView() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    writer << 10 << user.getUid();
    query(binaryData);
}

void MainWidget::s_addProduct() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    auto p = currentProductForm->getProduct();
    p.setUid(user.getUid());
    writer << 4 << p;//提交产品
    query(binaryData);
}

void MainWidget::s_changeProduct() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    auto p = currentProductForm->getProduct();
    p.setUid(user.getUid());
    writer << 5 << p;//修改产品
    query(binaryData);
}


void MainWidget::s_addOrder() {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    auto p = currentProductForm->getProduct();
    Order order;
    order.setUid(user.getUid());
    order.setSubmittime(QDateTime::currentDateTime().toString());
    order.setOstate(0);
    order.setOnum(1);
    order.setOpay(p.getPrice());
    order.setPid(p.getPid());
    writer << 7 << order << user;//添加购物车
    query(binaryData);
}

void MainWidget::s_sellerHandleOrder(bool accept) {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    auto order = currentOrderForm->getOrder();
    if (accept) {
        order.setOstate(2);
    } else {
        order.setOstate(3);
    }
    writer << 9 << order;//商家修改订单
    query(binaryData);
}


void MainWidget::popSellerProductView(QList<Product> &products) {
    qDebug() << products.size();
    QList<QWidget *> widgets;
    // 展示现有餐品
    for (auto &p:products) {
        auto pf = new ProductForm(this);
        pf->getFuncBtn()->setText("修改");
        pf->setProduct(p);
        pf->getUnameEdit()->setText(user.getUname());
        pf->getUnameEdit()->setDisabled(true);
        connect(pf->getFuncBtn(), &QToolButton::clicked, [=]() {
            currentProductForm = pf;
            s_changeProduct();
        });
        widgets.push_front(pf);
    }
    // 添加新产品的接口
    QToolButton *addBtn = new QToolButton();
    addBtn->setFixedSize(880, 220);
    addBtn->setText("点击添加产品...");
    connect(addBtn, &QToolButton::clicked, [=]() {
        qDebug() << "添加产品";
        auto pf = new ProductForm();
        pf->show();
        pf->getUnameEdit()->setText(user.getUname());
        pf->getUnameEdit()->setDisabled(true);
        pf->getFuncBtn()->setText("修改");
        connect(pf->getFuncBtn(), &QToolButton::clicked, [=]() {
            currentProductForm = pf;
            s_addProduct();
        });
    });
    widgets.push_front(addBtn);
    if (view != nullptr) {
        safeDelete(view);
    }
    view = new ViewWidget(this);
    view->setHint("商家餐饮产品");
    view->updateContent(widgets);
    userTodoForm->hide();
    view->show();

    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        safeDelete(view);
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked, [&]() {
        QMessageBox::StandardButton result = QMessageBox::information(
                nullptr,
                "确认刷新",
                "请确认修改的餐品信息已提交，否则变化的内容将不会被上传",
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
        );
        switch (result) {
            case QMessageBox::Yes:
            safeDelete(view);
                s_sellerProductView();
                break;
            case QMessageBox::No:
                break;
            default:
                break;
        }
    });
}

void MainWidget::popBuyerProductView(QList<Product> &products) {
    qDebug() << products.size();
    QList<QWidget *> widgets;
    // 展示现有餐品
    for (auto &p:products) {
        auto pf = new ProductForm(this);
        pf->setProduct(p);
        pf->setDisplayOnly();
        connect(pf->getFuncBtn(), &QToolButton::clicked, [=]() {
            QMessageBox::StandardButton result = QMessageBox::information(
                    nullptr,
                    "确认添加购物车",
                    "确定要将该餐品添加到购物车吗？",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
            );
            switch (result) {
                case QMessageBox::Yes:
                    currentProductForm = pf;
                    s_addOrder();
                    break;
                case QMessageBox::No:
                    break;
                default:
                    break;
            }
        });
        widgets.push_front(pf);
    }
    if (view != nullptr) {
        safeDelete(view);
    }
    view = new ViewWidget(this);
    view->setHint("在售餐饮产品");
    view->updateContent(widgets);
    userTodoForm->hide();
    view->show();

    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        safeDelete(view);
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked, [&]() {
        safeDelete(view);
        s_buyerProductView();
    });
}

void MainWidget::popSellerOrderView(QList<OrderAdapter> &orders) {
    QList<QWidget *> widgets;
    if (view != nullptr) {
        safeDelete(view);
    }
    view = new ViewWidget(this);
    view->setHint("我的订单");
    for (auto &o:orders) {
        auto orderForm = new OrderForm(view);
        orderForm->setOrder(o);
        orderForm->setSellerMode();
        widgets.push_front(orderForm);
        connect(orderForm->getBtn1(), &QToolButton::clicked, [=]() {
            QMessageBox::StandardButton result = QMessageBox::information(
                    nullptr,
                    "接受订单",
                    "确认接受订单吗？",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
            );
            switch (result) {
                case QMessageBox::Yes:
                    currentOrderForm = orderForm;
                    s_sellerHandleOrder(true);
                    safeDelete(view);
                    break;
                case QMessageBox::No:
                    break;
                default:
                    break;
            }
        });
        connect(orderForm->getBtn2(), &QToolButton::clicked, [=]() {
            QMessageBox::StandardButton result = QMessageBox::information(
                    nullptr,
                    "拒收订单",
                    "确认拒收订单吗？",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
            );
            switch (result) {
                case QMessageBox::Yes:
                    currentOrderForm = orderForm;
                    s_sellerHandleOrder(false);
                    safeDelete(view);
                    break;
                case QMessageBox::No:
                    break;
                default:
                    break;
            }
        });
    }
    view->updateContent(widgets);
    userTodoForm->hide();
    view->show();
    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        safeDelete(view);
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked, [&]() {
        safeDelete(view);
        s_sellerOrderView();
    });
}

void MainWidget::popBuyerOrderView(QList<OrderAdapter> &orders) {
    QList<QWidget *> widgets;
    if (view != nullptr) {
        safeDelete(view);
    }
    view = new ViewWidget(this);
    view->setHint("我的购物车");
    for (auto &o:orders) {
        auto orderForm = new OrderForm(view);
        orderForm->setOrder(o);
        orderForm->setBuyerMode();
        widgets.push_front(orderForm);
        connect(orderForm->getBtn1(), &QToolButton::clicked, [=]() {
            QMessageBox::StandardButton result = QMessageBox::information(
                    nullptr,
                    "提交订单",
                    "确认提交订单吗？",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
            );
            switch (result) {
                case QMessageBox::Yes:
                    currentOrderForm = orderForm;
                    s_buyerHandleOrder(true);
                    safeDelete(view);
                    break;
                case QMessageBox::No:
                    break;
                default:
                    break;
            }
        });
        connect(orderForm->getBtn2(), &QToolButton::clicked, [=]() {
            QMessageBox::StandardButton result = QMessageBox::information(
                    nullptr,
                    "移出购物车",
                    "确认删除商品吗？",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
            );
            switch (result) {
                case QMessageBox::Yes:
                    currentOrderForm = orderForm;
                    s_buyerHandleOrder(false);
                    safeDelete(view);
                    break;
                case QMessageBox::No:
                    break;
                default:
                    break;
            }
        });
    }
    view->updateContent(widgets);
    userTodoForm->hide();
    view->show();
    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        safeDelete(view);
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked, [&]() {
        safeDelete(view);
        s_buyerOrderView();
    });
}

void MainWidget::s_buyerHandleOrder(bool accept) {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    auto order = currentOrderForm->getOrder();
    order.setSubmittime(QDateTime::currentDateTime().toString());
    if (accept) {
        order.setOstate(1);
    } else {
        order.setOstate(4);
    }
    writer << 11 << order<<user;//用户修改订单
    query(binaryData);
}
