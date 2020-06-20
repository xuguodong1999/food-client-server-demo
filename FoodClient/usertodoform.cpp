#include "usertodoform.h"
#include "ui_usertodoform.h"

UserTodoForm::UserTodoForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::UserTodoForm) {
    ui->setupUi(this);
}

UserTodoForm::~UserTodoForm() {
    delete ui;
}

QLabel *UserTodoForm::getHint() {
    return ui->hint;
}

QToolButton *UserTodoForm::getBtn1() {
    return ui->btn1;
}

QToolButton *UserTodoForm::getBtn2() {
    return ui->btn2;
}

QLabel *UserTodoForm::getUinfo() {
    return ui->uinfo;
}

void UserTodoForm::setUser(const User &user) {
    switch (user.getUtype()) {
        case 1:
            getUinfo()->setText("欢迎订餐者：" + user.getUname());
            break;
        case 3:
            getUinfo()->setText("欢迎vip1：" + user.getUname());
            break;
        case 4:
            getUinfo()->setText("欢迎vip2：" + user.getUname());
            break;
    }
}

void SellerTodoBuilder::buildUserInfo(const User &user) {
    userTodoForm->getHint()->setText("商家服务");
    userTodoForm->getUinfo()->setText("欢迎商家：" + user.getUname());
}

void BuyerTodoBuilder::buildBtn1() {
    userTodoForm->getBtn1()->setText("查看餐品");
}

void BuyerTodoBuilder::buildBtn2() {
    userTodoForm->getBtn2()->setText("查看购物车");
}

void BuyerTodoBuilder::buildUserInfo(const User &user) {
    userTodoForm->getHint()->setText("订餐者服务");
    userTodoForm->setUser(user);
}

void SellerTodoBuilder::buildBtn1() {
    userTodoForm->getBtn1()->setText("管理餐品");
}

void SellerTodoBuilder::buildBtn2() {
    userTodoForm->getBtn2()->setText("管理订单");
}

void AdminTodoBuilder::buildUserInfo(const User &user) {
    userTodoForm->getHint()->setText("管理员服务");
    userTodoForm->getUinfo()->setText("欢迎管理员：" + user.getUname());
}

void AdminTodoBuilder::buildBtn1() {
    userTodoForm->getBtn1()->setText("统计月销售额");
}

void AdminTodoBuilder::buildBtn2() {
    userTodoForm->getBtn2()->setText("统计周销售额");
}

UserTodoBuilder::UserTodoBuilder() {
    userTodoForm = new UserTodoForm();
}

UserTodoForm *UserTodoBuilder::createTodoForm() {
    return userTodoForm;
}

UserTodoForm *TodoFormController::createUserTodoForm(UserTodoBuilder *todoBuilder, const User &user) {
    todoBuilder->buildBtn1();
    todoBuilder->buildBtn2();
    todoBuilder->buildUserInfo(user);
    return todoBuilder->createTodoForm();
}
