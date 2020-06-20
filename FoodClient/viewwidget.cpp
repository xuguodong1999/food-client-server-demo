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
