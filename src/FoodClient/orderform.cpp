#include "orderform.h"
#include "ui_orderform.h"

OrderForm::OrderForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::OrderForm) {
    ui->setupUi(this);
    connect(getOnumBox(), QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        ui->opay->setValue(value * order.getPrice());
        if (order.getOstate() != 2) {
            order.setOnum(value);
        }
    });
}

OrderForm::~OrderForm() {
    delete ui;
}

QToolButton *OrderForm::getPhotoBtn() {
    return ui->photo;
}

QToolButton *OrderForm::getBtn1() {
    return ui->btn1;
}

QToolButton *OrderForm::getBtn2() {
    return ui->btn2;
}

QLineEdit *OrderForm::getPnameEdit() {
    return ui->pname;
}

QLineEdit *OrderForm::getUpdateEdit() {
    return ui->update;
}

QDoubleSpinBox *OrderForm::getOpayBox() {
    return ui->opay;
}

QSpinBox *OrderForm::getOnumBox() {
    return ui->onum;
}

QComboBox *OrderForm::getOstateBox() {
    return ui->ostate;
}

void OrderForm::setOrder(const OrderWithFullInfo &o) {
    order = o;
    QByteArray imageData = QByteArray::fromBase64(order.getPhoto().toLatin1());
    QPixmap image;
    image.loadFromData(imageData);
    ui->photo->setIcon(QIcon(image));
    ui->pname->setText(order.getPname());
    ui->update->setText(order.getSubmittime());
    ui->ostate->setCurrentIndex(order.getOstate());
    ui->onum->setValue(order.getOnum());
    ui->opay->setValue(order.getOpay());
}

void OrderForm::setBuyerMode() {
    getOstateBox()->setDisabled(true);
    getOpayBox()->setDisabled(true);
    getPnameEdit()->setFocusPolicy(Qt::NoFocus);
    getUpdateEdit()->setFocusPolicy(Qt::NoFocus);
    getBtn1()->setText("结算");
    getBtn2()->setText("删除");
    switch (order.getOstate()) {
        case submit:
            getBtn1()->setDisabled(true);
            getOnumBox()->setDisabled(true);
        case done:
        case sellerReject:
        case userDelete:
            getBtn1()->setDisabled(true);
            getBtn2()->setDisabled(true);
            getOnumBox()->setDisabled(true);
    }
}

void OrderForm::setSellerMode() {
    getOstateBox()->setDisabled(true);
    getOnumBox()->setDisabled(true);
    getOpayBox()->setDisabled(true);
    getPnameEdit()->setFocusPolicy(Qt::NoFocus);
    getUpdateEdit()->setFocusPolicy(Qt::NoFocus);
    getBtn1()->setText("接受");
    getBtn2()->setText("拒收");
    switch (order.getOstate()) {
        case done:
        case sellerReject:
        case userDelete:
            getBtn1()->setDisabled(true);
            getBtn2()->setDisabled(true);
    }
}

OrderWithFullInfo OrderForm::getOrder() {
    return order;
}
