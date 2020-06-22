#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QWidget>
#include <QToolButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include "order.h"

namespace Ui {
    class OrderForm;
}

class OrderForm : public QWidget {
Q_OBJECT

public:
    explicit OrderForm(QWidget *parent = nullptr);

    ~OrderForm();

    void setOrder(const OrderWithFullInfo &o);

    void setBuyerMode();

    void setSellerMode();

    OrderWithFullInfo getOrder();

    QToolButton *getPhotoBtn();

    QToolButton *getBtn1();

    QToolButton *getBtn2();

    QLineEdit *getPnameEdit();

    QLineEdit *getUpdateEdit();

    QDoubleSpinBox *getOpayBox();

    QSpinBox *getOnumBox();

    QComboBox *getOstateBox();

private:
    Ui::OrderForm *ui;
    OrderWithFullInfo order;
};

#endif // ORDERFORM_H
