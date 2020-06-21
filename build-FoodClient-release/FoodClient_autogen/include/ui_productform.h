/********************************************************************************
** Form generated from reading UI file 'productform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTFORM_H
#define UI_PRODUCTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductForm
{
public:
    QToolButton *photo;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *unameLabel;
    QLineEdit *uname;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *pname;
    QToolButton *btn;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *pstate;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *pinfo;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *price;

    void setupUi(QWidget *ProductForm)
    {
        if (ProductForm->objectName().isEmpty())
            ProductForm->setObjectName(QString::fromUtf8("ProductForm"));
        ProductForm->resize(880, 220);
        ProductForm->setMinimumSize(QSize(600, 220));
        photo = new QToolButton(ProductForm);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(10, 10, 200, 200));
        photo->setMinimumSize(QSize(200, 200));
        photo->setMaximumSize(QSize(200, 200));
        photo->setIconSize(QSize(200, 200));
        layoutWidget = new QWidget(ProductForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(240, 10, 601, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        unameLabel = new QLabel(layoutWidget);
        unameLabel->setObjectName(QString::fromUtf8("unameLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        unameLabel->setFont(font);

        horizontalLayout->addWidget(unameLabel);

        uname = new QLineEdit(layoutWidget);
        uname->setObjectName(QString::fromUtf8("uname"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uname->sizePolicy().hasHeightForWidth());
        uname->setSizePolicy(sizePolicy);
        uname->setFont(font);

        horizontalLayout->addWidget(uname);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);
        layoutWidget_2 = new QWidget(ProductForm);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(240, 60, 601, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, 3, 3, 3);
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        pname = new QLineEdit(layoutWidget_2);
        pname->setObjectName(QString::fromUtf8("pname"));
        sizePolicy.setHeightForWidth(pname->sizePolicy().hasHeightForWidth());
        pname->setSizePolicy(sizePolicy);
        pname->setFont(font);

        horizontalLayout_2->addWidget(pname);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);
        btn = new QToolButton(ProductForm);
        btn->setObjectName(QString::fromUtf8("btn"));
        btn->setGeometry(QRect(670, 160, 171, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        btn->setFont(font1);
        layoutWidget_4 = new QWidget(ProductForm);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(240, 160, 171, 51));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(3, 3, 3, 3);
        label_4 = new QLabel(layoutWidget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        pstate = new QComboBox(layoutWidget_4);
        pstate->addItem(QString());
        pstate->addItem(QString());
        pstate->setObjectName(QString::fromUtf8("pstate"));
        sizePolicy.setHeightForWidth(pstate->sizePolicy().hasHeightForWidth());
        pstate->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(9);
        pstate->setFont(font2);

        horizontalLayout_4->addWidget(pstate);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 3);
        layoutWidget_3 = new QWidget(ProductForm);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(240, 110, 601, 41));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(3, 3, 3, 3);
        label_3 = new QLabel(layoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        pinfo = new QLineEdit(layoutWidget_3);
        pinfo->setObjectName(QString::fromUtf8("pinfo"));
        sizePolicy.setHeightForWidth(pinfo->sizePolicy().hasHeightForWidth());
        pinfo->setSizePolicy(sizePolicy);
        pinfo->setFont(font);

        horizontalLayout_3->addWidget(pinfo);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);
        layoutWidget1 = new QWidget(ProductForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(440, 160, 211, 51));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(3, 3, 3, 3);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        price = new QDoubleSpinBox(layoutWidget1);
        price->setObjectName(QString::fromUtf8("price"));
        sizePolicy.setHeightForWidth(price->sizePolicy().hasHeightForWidth());
        price->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(9);
        price->setFont(font3);
        price->setMaximum(10000.000000000000000);

        horizontalLayout_5->addWidget(price);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 3);

        retranslateUi(ProductForm);

        QMetaObject::connectSlotsByName(ProductForm);
    } // setupUi

    void retranslateUi(QWidget *ProductForm)
    {
        ProductForm->setWindowTitle(QCoreApplication::translate("ProductForm", "Form", nullptr));
        photo->setText(QCoreApplication::translate("ProductForm", "\351\244\220\345\223\201\345\233\276\347\211\207", nullptr));
        unameLabel->setText(QCoreApplication::translate("ProductForm", "\345\225\206\345\256\266", nullptr));
        label_2->setText(QCoreApplication::translate("ProductForm", "\351\244\220\345\223\201", nullptr));
        btn->setText(QCoreApplication::translate("ProductForm", "\345\212\237\350\203\275", nullptr));
        label_4->setText(QCoreApplication::translate("ProductForm", "\347\212\266\346\200\201", nullptr));
        pstate->setItemText(0, QCoreApplication::translate("ProductForm", "\351\224\200\345\224\256\344\270\255", nullptr));
        pstate->setItemText(1, QCoreApplication::translate("ProductForm", "\344\270\213\346\236\266", nullptr));

        label_3->setText(QCoreApplication::translate("ProductForm", "\344\273\213\347\273\215", nullptr));
        label_5->setText(QCoreApplication::translate("ProductForm", "\345\215\225\344\273\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductForm: public Ui_ProductForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTFORM_H
