#ifndef PRODUCTFORM_H
#define PRODUCTFORM_H

#include "product.h"
#include <QWidget>
#include <QToolButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>

namespace Ui {
    class ProductForm;
}

class ProductForm : public QWidget {
Q_OBJECT

public:
    explicit ProductForm(QWidget *parent = nullptr);

    ~ProductForm();

    QToolButton *getPhotoBtn();

    QToolButton *getFuncBtn();

    QLineEdit *getUnameEdit();

    QLineEdit *getPnameEdit();

    QLineEdit *getPinfoEdit();

    QDoubleSpinBox *getPriceBox();

    QComboBox *getPstateBox();

    void setProduct(const Product &product);

    Product getProduct();

    void setDisplayOnly();

private:
    Ui::ProductForm *ui;
    Product p;
    bool isSellerForm;
};

#endif // PRODUCTFORM_H
