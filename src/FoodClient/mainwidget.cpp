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
#include <QThread>

MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent), isConnected(false), userform(nullptr), view(nullptr),
        userTodoForm(nullptr), currentProductForm(nullptr), currentOrderForm(nullptr) {
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    userform = new UserForm(this);
    socket = new QTcpSocket();
    socket->abort();
    socket->connectToHost(addr, port);
    connect(socket, &QTcpSocket::connected, [=]() { isConnected = true; });
    connect(socket, &QTcpSocket::disconnected, [=]() {
        isConnected = false;
        socket->close();
        socket->deleteLater();
        socket = nullptr;
    });
    // 响应注册按钮点击
    connect(userform->getRegister(), &QToolButton::clicked, [=]() {
        QByteArray buffer;
        QDataStream writer(&buffer, QIODevice::WriteOnly);
        writer << USER_REGISTER << userform->getUser();//提交注册信息
        send(buffer);
    });
    // 响应登录按钮点击
    connect(userform->getLogin(), &QToolButton::clicked, [=]() {
        QByteArray buffer;
        QDataStream writer(&buffer, QIODevice::WriteOnly);
        writer << USER_LOGIN << userform->getUser();//提交登录信息
        send(buffer);
    });
    // 响应服务器消息
    connect(socket, &QTcpSocket::readyRead, [=]() {
        // 处理网络流，socket->readAll()函数只读一个tcp包
        // qt会把一次较大的socket->write分成若干个小包发过来
        // 没有提供一次读完的接口。。。使用长度标识实现完整读取
        QDataStream preReader(&toAppendBuffer, QIODevice::ReadOnly);
        auto tmp = socket->readAll();
        if (toAppendBuffer.isEmpty()) {
            toAppendBuffer.append(tmp);
            preReader >> toReceiveBufferSize;
            if (toAppendBuffer.size() < toReceiveBufferSize) {
                return;
            }
        } else {
            toAppendBuffer.append(tmp);
//            qDebug() << "当前长度：" << toAppendBuffer.length();
            if (toAppendBuffer.size() < toReceiveBufferSize) {
//                qDebug() << "继续读取...";
                return;
            }
        }
        QDataStream reader(&toAppendBuffer, QIODevice::ReadOnly);
        reader >> toReceiveBufferSize;
        int taskid;
        reader >> taskid;
        process(TaskId(taskid), reader);
        toAppendBuffer.clear();
    });
}

MainWidget::~MainWidget() {
}

void MainWidget::send(const QByteArray &binaryData) {
    if (!isConnected) {
        socket->abort();
        socket->connectToHost(addr, port);
        QThread::msleep(10);
        if (!isConnected) {
            popWarning("连接服务器失败");
        }
        return;
    }
    socket->write(binaryData);
}

void MainWidget::requestSellerProductView() {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    writer << SELLER_VIEW_PRODUCT << user.getUid();//提交商家身份
    send(buffer);
}

void MainWidget::requestSellerOrderView() {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    writer << SELLER_VIEW_ORDER << user.getUid();
    send(buffer);
}

void MainWidget::requestBuyerProductView() {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    writer << BUYER_VIEW_PRODUCT;
    send(buffer);
}

void MainWidget::requestBuyerOrderView() {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    writer << USER_VIEW_ORDER << user.getUid();
    send(buffer);
}

void MainWidget::requestSellerAddProduct() {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    auto p = currentProductForm->getProduct();
    p.setUid(user.getUid());
    writer << SELLER_ADD_PRODUCT << p;//提交产品
    send(buffer);
}

void MainWidget::requestSellerChangeProduct() {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    auto p = currentProductForm->getProduct();
    p.setUid(user.getUid());
    writer << SELLER_CHANGE_PRODUCT << p;//修改产品
    send(buffer);
}

void MainWidget::requestUserAddOrder() {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    auto p = currentProductForm->getProduct();
    Order order;
    order.setUid(user.getUid());
    order.setSubmittime(QDateTime::currentDateTime().toString());
    order.setOstate(incart);
    order.setOnum(1);
    order.setOpay(p.getPrice());
    order.setPid(p.getPid());
    writer << BUYER_ADD_ORDER << order << user;//添加购物车
    send(buffer);
}

void MainWidget::requestSellerChangeOrder(bool accept) {
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    auto order = currentOrderForm->getOrder();
    if (accept) {
        order.setOstate(done);
    } else {
        order.setOstate(sellerReject);
    }
    writer << SELLER_CHANGE_ORDER << order;//商家修改订单
    send(buffer);
}

void MainWidget::popSellerProductView(QList<Product> &products) {
//    qDebug() << products.size();
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
            requestSellerChangeProduct();
        });
        widgets.push_front(pf);
    }
    // 添加新产品的接口
    QToolButton *addBtn = new QToolButton();
    addBtn->setFixedSize(getSubWindowSize());
    addBtn->setText("点击添加产品...");
    connect(addBtn, &QToolButton::clicked, [=]() {
//        qDebug() << "添加产品";
        auto pf = new ProductForm();
        pf->show();
        pf->getUnameEdit()->setText(user.getUname());
        pf->getUnameEdit()->setDisabled(true);
        pf->getFuncBtn()->setText("添加");
        connect(pf->getFuncBtn(), &QToolButton::clicked, [=]() {
            currentProductForm = pf;
            requestSellerAddProduct();
        });
    });
    widgets.push_front(addBtn);
    updateView();
    view->setHint("商家餐饮产品");
    view->updateContent(widgets);// 在这里完成树形关系的绑定，避免内存泄漏
    userTodoForm->hide();
    view->show();
    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        closeView();
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked,
            this, &MainWidget::popSellerRefreshProductMessage);
}

void MainWidget::popBuyerProductView(QList<Product> &products) {
//    qDebug() << products.size();
    QList<QWidget *> widgets;
    // 展示现有餐品
    for (auto &p:products) {
        auto pf = new ProductForm(this);
        pf->setProduct(p);
        pf->setDisplayOnly();
        connect(pf->getFuncBtn(), &QToolButton::clicked, [=]() {
            currentProductForm = pf;
            popBuyerAddOrderMessage();
        });
        widgets.push_front(pf);
    }
    updateView();
    view->setHint("在售餐饮产品");
    view->updateContent(widgets);
    userTodoForm->hide();
    view->show();
    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        closeView();
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked, [&]() {
        closeView();
        requestBuyerProductView();
    });
}

void MainWidget::popSellerOrderView(QList<OrderWithFullInfo> &orders) {
    QList<QWidget *> widgets;
    updateView();
    view->setHint("我的订单");
    for (auto &o:orders) {
        auto orderForm = new OrderForm(view);
        orderForm->setOrder(o);
        orderForm->setSellerMode();
        widgets.push_front(orderForm);
        connect(orderForm->getBtn1(), &QToolButton::clicked, [=]() {
            currentOrderForm = orderForm;
            popSellerAcceptOrderMessage();

        });
        connect(orderForm->getBtn2(), &QToolButton::clicked, [=]() {
            currentOrderForm = orderForm;
            popSellerCancelOrderMessage();
        });
    }
    view->updateContent(widgets);
    userTodoForm->hide();
    view->show();
    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        closeView();
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked, [&]() {
        closeView();
        requestSellerOrderView();
    });
}

void MainWidget::popBuyerOrderView(QList<OrderWithFullInfo> &orders) {
    QList<QWidget *> widgets;
    updateView();
    view->setHint("我的购物车");
    for (auto &o:orders) {
        auto orderForm = new OrderForm(view);
        orderForm->setOrder(o);
        orderForm->setBuyerMode();
        widgets.push_front(orderForm);
        connect(orderForm->getBtn1(), &QToolButton::clicked, [=]() {
            currentOrderForm = orderForm;
            popBuyerSubmitOrderMessage();
        });
        connect(orderForm->getBtn2(), &QToolButton::clicked, [=]() {
            currentOrderForm = orderForm;
            popBuyerCancelOrderMessage();
        });
    }
    view->updateContent(widgets);
    userTodoForm->hide();
    view->show();
    connect(view->getBackBtn(), &QToolButton::clicked, [=]() {
        closeView();
        userTodoForm->show();
    });
    connect(view->getUpdateBtn(), &QToolButton::clicked, [&]() {
        closeView();
        requestBuyerOrderView();
    });
}

void MainWidget::requestBuyerChangeOrder(bool accept) {
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    auto order = currentOrderForm->getOrder();
    order.setSubmittime(QDateTime::currentDateTime().toString());
    if (accept) {
        order.setOstate(submit);
    } else {
        order.setOstate(userDelete);
    }
    writer << USER_CHANGE_ORDER << order << user;//订餐者修改订单
    send(binaryData);
}

void MainWidget::updateView() {
    if (view != nullptr) {
        closeView();
    }
    view = new ViewWidget(this);
    view->setUinfo(user);
}

void MainWidget::closeView() {
    view->close();
    view->deleteLater();
    view = nullptr;
}

void MainWidget::closeProductForm() {
    currentProductForm->close();
    currentProductForm->deleteLater();
    currentProductForm = nullptr;
}

void MainWidget::requestMonthSaleCount() {
    //发一条信息查询月销售额
    QByteArray buffer;
    QDataStream writer(&buffer, QIODevice::WriteOnly);
    writer << COUNT_MONTH_SALE;
    send(buffer);
}

void MainWidget::requestWeekSaleCount() {
    //发一条信息查询周销售额
    QByteArray binaryData;
    QDataStream writer(&binaryData, QIODevice::WriteOnly);
    writer << COUNT_WEEK_SALE;
    send(binaryData);
}

void MainWidget::popUserTodoForm(const User &user) {
//    qDebug() << user.getUname() << "登录成功";
    TodoFormBuilder *builder;
    TodoFormController controller;
    switch (user.getUtype()) {
        case seller:
            builder = new SellerTodoBuilder();
            userTodoForm = controller.createUserTodoForm(builder, user);
            connect(userTodoForm->getBtn1(), &QToolButton::clicked,
                    this, &MainWidget::requestSellerProductView);
            connect(userTodoForm->getBtn2(), &QToolButton::clicked,
                    this, &MainWidget::requestSellerOrderView);
            break;
        case admin:
            builder = new AdminTodoBuilder();
            userTodoForm = controller.createUserTodoForm(builder, user);
            // 管理员
            connect(userTodoForm->getBtn1(), &QToolButton::clicked,
                    this, &MainWidget::requestMonthSaleCount);
            connect(userTodoForm->getBtn2(), &QToolButton::clicked,
                    this, &MainWidget::requestWeekSaleCount);
            break;
        case buyer:
        case vip1:
        case vip2:
            builder = new BuyerTodoBuilder();
            userTodoForm = controller.createUserTodoForm(builder, user);
            connect(userTodoForm->getBtn1(), &QToolButton::clicked,
                    this, &MainWidget::requestBuyerProductView);
            connect(userTodoForm->getBtn2(), &QToolButton::clicked,
                    this, &MainWidget::requestBuyerOrderView);
    }
    delete builder;
    userTodoForm->setParent(this);
    userform->close();
    userTodoForm->show();
}

void MainWidget::popBuyerSubmitOrderMessage() {
    QMessageBox::StandardButton result = QMessageBox::information(
            nullptr,
            "提交订单",
            "确认提交订单吗？",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
    );
    switch (result) {
        case QMessageBox::Yes:
            requestBuyerChangeOrder(true);
            closeView();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWidget::popBuyerCancelOrderMessage() {
    QMessageBox::StandardButton result = QMessageBox::information(
            nullptr,
            "移出购物车",
            "确认删除商品吗？",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
    );
    switch (result) {
        case QMessageBox::Yes:
            requestBuyerChangeOrder(false);
            closeView();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWidget::popBuyerAddOrderMessage() {
    QMessageBox::StandardButton result = QMessageBox::information(
            nullptr,
            "确认添加购物车",
            "确定要将该餐品添加到购物车吗？",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
    );
    switch (result) {
        case QMessageBox::Yes:
            requestUserAddOrder();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWidget::popSellerAcceptOrderMessage() {
    QMessageBox::StandardButton result = QMessageBox::information(
            nullptr,
            "接受订单",
            "确认接受订单吗？",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
    );
    switch (result) {
        case QMessageBox::Yes:
            requestSellerChangeOrder(true);
            closeView();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWidget::popSellerCancelOrderMessage() {
    QMessageBox::StandardButton result = QMessageBox::information(
            nullptr,
            "拒收订单",
            "确认拒收订单吗？",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
    );
    switch (result) {
        case QMessageBox::Yes:
            requestSellerChangeOrder(false);
            closeView();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWidget::popSellerRefreshProductMessage() {
    QMessageBox::StandardButton result = QMessageBox::information(
            nullptr,
            "确认刷新",
            "请确认修改的餐品信息已提交，否则变化的内容将不会被上传",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
    );
    switch (result) {
        case QMessageBox::Yes:
            closeView();
            requestSellerProductView();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWidget::popWarning(const QString &info) {
    QMessageBox::information(nullptr, "提示",
                             info, QMessageBox::Yes);
}

void MainWidget::popBuyerGotoOrderViewMessage(const QString &info) {
    QMessageBox::StandardButton result = QMessageBox::information(
            nullptr,
            "成功添加到购物车",
            info + "去购物车结算吗",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
    );
    switch (result) {
        case QMessageBox::Yes:
            closeView();
            requestBuyerOrderView();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWidget::process(TaskId taskid, QDataStream &reader) {
    QByteArray result;
    QDataStream writter(&result, QIODevice::WriteOnly);
    bool success;
    reader >> success;
    switch (TaskId(taskid)) {
        case USER_REGISTER:
        case USER_LOGIN: {//收到添加新用户的回复
            if (!success) {
                popWarning("登录失败");
            } else {
                reader >> user;
                // 跳转功能界面
                userform->update(user);
                popUserTodoForm(user);
            }
            break;
        }
        case SELLER_VIEW_PRODUCT : {// 收到商家产品数据
            if (!success) {
                popWarning("查询失败");
            } else {
                QList<Product> products;
                reader >> products;
                popSellerProductView(products);
            }
            break;
        }
        case SELLER_ADD_PRODUCT : {//添加产品
            if (!success) {
                popWarning("添加失败");
            } else {
                closeProductForm();
                popWarning("添加成功");
                QList<Product> products;
                reader >> products;
                popSellerProductView(products);
            }
            break;
        }
        case SELLER_CHANGE_PRODUCT: {//修改产品
            if (!success) {
                popWarning("修改失败");
            } else {
                popWarning("修改成功");
                QList<Product> products;
                reader >> products;
                popSellerProductView(products);
            }
            break;
        }
        case BUYER_VIEW_PRODUCT: {// 收到订餐者推荐产品
            if (!success) {
                popWarning("查询失败");
            } else {
                QList<Product> products;
                reader >> products;
                popBuyerProductView(products);
            }
            break;
        }
        case BUYER_ADD_ORDER: {
            if (!success) {
                popWarning("添加购物车失败");
            } else {
                QString info;
                reader >> info;
                popBuyerGotoOrderViewMessage(info);
            }
            break;
        }
        case SELLER_VIEW_ORDER:
        case SELLER_CHANGE_ORDER: {//刷新商家订单
            if (!success) {
                popWarning("查询失败");
            } else {
                QList<OrderWithFullInfo> orders;
                reader >> orders;
                popSellerOrderView(orders);
            }
            break;
        }
        case USER_VIEW_ORDER:
        case USER_CHANGE_ORDER: {//刷新用户订单
            if (!success) {
                popWarning("查询失败");
            } else {
                QList<OrderWithFullInfo> orders;
                reader >> orders;
                popBuyerOrderView(orders);
            }
            break;
        }
        case COUNT_MONTH_SALE:
        case COUNT_WEEK_SALE: {
            if (!success) {
                popWarning("查询失败");
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
}
