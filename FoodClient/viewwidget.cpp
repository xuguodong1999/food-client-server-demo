#include "viewwidget.h"
#include "ui_viewwidget.h"
#include <QGridLayout>

ViewWidget::ViewWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ViewWidget) {
    ui->setupUi(this);
}

ViewWidget::~ViewWidget() {
    delete ui;
}

QScrollArea *ViewWidget::getContent() {
    return ui->scrollArea;
}

void ViewWidget::updateContent(QList<QWidget *> &widgets) {
    QGridLayout *pLayout = new QGridLayout();
    for (auto &i:widgets) {
        i->setParent(this);
        pLayout->addWidget(i);
    }
    auto c = getContent();
    c->widget()->setLayout(pLayout);
}

QToolButton *ViewWidget::getBackBtn() {
    return ui->back;
}

void ViewWidget::setHint(const QString &hint) {
    ui->hint->setText(hint);
}

QToolButton *ViewWidget::getUpdateBtn() {
    return ui->update;
}

void ViewWidget::setUinfo(const User &user) {
    switch (Utype(user.getUtype())) {
        case buyer:
            ui->uinfo->setText("欢迎订餐者：" + user.getUname());
            break;
        case seller:
            ui->uinfo->setText("欢迎商家：" + user.getUname());
            break;
        case vip1:
            ui->uinfo->setText("欢迎vip1：" + user.getUname());
            break;
        case vip2:
            ui->uinfo->setText("欢迎vip2：" + user.getUname());
            break;
    }
}
