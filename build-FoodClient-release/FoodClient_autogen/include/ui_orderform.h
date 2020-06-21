/********************************************************************************
** Form generated from reading UI file 'orderform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERFORM_H
#define UI_ORDERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderForm
{
public:
    QToolButton *photo;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *opay;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *update;
    QToolButton *btn1;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *pname;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *onum;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *ostate;
    QToolButton *btn2;

    void setupUi(QWidget *OrderForm)
    {
        if (OrderForm->objectName().isEmpty())
            OrderForm->setObjectName(QString::fromUtf8("OrderForm"));
        OrderForm->resize(880, 220);
        OrderForm->setMinimumSize(QSize(600, 220));
        photo = new QToolButton(OrderForm);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(10, 10, 200, 200));
        photo->setMinimumSize(QSize(200, 200));
        photo->setMaximumSize(QSize(200, 200));
        photo->setIconSize(QSize(200, 200));
        layoutWidget_2 = new QWidget(OrderForm);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(450, 120, 221, 51));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(3, 3, 3, 3);
        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        opay = new QDoubleSpinBox(layoutWidget_2);
        opay->setObjectName(QString::fromUtf8("opay"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setBold(true);
        font1.setWeight(75);
        opay->setFont(font1);
        opay->setMaximum(1000000.000000000000000);

        horizontalLayout_5->addWidget(opay);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 3);
        layoutWidget_3 = new QWidget(OrderForm);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(240, 70, 631, 51));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(3, 3, 3, 3);
        label_3 = new QLabel(layoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        update = new QLineEdit(layoutWidget_3);
        update->setObjectName(QString::fromUtf8("update"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(update->sizePolicy().hasHeightForWidth());
        update->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        update->setFont(font2);

        horizontalLayout_3->addWidget(update);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);
        btn1 = new QToolButton(OrderForm);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(360, 170, 200, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        btn1->setFont(font3);
        layoutWidget_5 = new QWidget(OrderForm);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(240, 10, 631, 51));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, 3, 3, 3);
        label_2 = new QLabel(layoutWidget_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        pname = new QLineEdit(layoutWidget_5);
        pname->setObjectName(QString::fromUtf8("pname"));
        sizePolicy.setHeightForWidth(pname->sizePolicy().hasHeightForWidth());
        pname->setSizePolicy(sizePolicy);
        pname->setFont(font2);

        horizontalLayout_2->addWidget(pname);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);
        layoutWidget_4 = new QWidget(OrderForm);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(240, 120, 191, 51));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(3, 3, 3, 3);
        label_6 = new QLabel(layoutWidget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        horizontalLayout_6->addWidget(label_6);

        onum = new QSpinBox(layoutWidget_4);
        onum->setObjectName(QString::fromUtf8("onum"));
        onum->setFont(font1);
        onum->setMaximum(100);

        horizontalLayout_6->addWidget(onum);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 3);
        layoutWidget_6 = new QWidget(OrderForm);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(690, 120, 181, 51));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(10, 10, 10, 10);
        label_4 = new QLabel(layoutWidget_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        ostate = new QComboBox(layoutWidget_6);
        ostate->addItem(QString());
        ostate->addItem(QString());
        ostate->addItem(QString());
        ostate->addItem(QString());
        ostate->addItem(QString());
        ostate->setObjectName(QString::fromUtf8("ostate"));
        sizePolicy.setHeightForWidth(ostate->sizePolicy().hasHeightForWidth());
        ostate->setSizePolicy(sizePolicy);
        ostate->setFont(font1);

        horizontalLayout_4->addWidget(ostate);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 3);
        btn2 = new QToolButton(OrderForm);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(590, 170, 200, 41));
        btn2->setFont(font3);

        retranslateUi(OrderForm);

        QMetaObject::connectSlotsByName(OrderForm);
    } // setupUi

    void retranslateUi(QWidget *OrderForm)
    {
        OrderForm->setWindowTitle(QCoreApplication::translate("OrderForm", "Form", nullptr));
        photo->setText(QCoreApplication::translate("OrderForm", "\351\244\220\345\223\201\345\233\276\347\211\207", nullptr));
        label_5->setText(QCoreApplication::translate("OrderForm", "\346\200\273\344\273\267", nullptr));
        label_3->setText(QCoreApplication::translate("OrderForm", "\346\234\200\350\277\221\346\233\264\346\226\260", nullptr));
        update->setText(QString());
        btn1->setText(QCoreApplication::translate("OrderForm", "\347\273\223\347\256\227", nullptr));
        label_2->setText(QCoreApplication::translate("OrderForm", "\351\244\220\345\223\201", nullptr));
        pname->setText(QString());
        label_6->setText(QCoreApplication::translate("OrderForm", "\346\225\260\351\207\217", nullptr));
        label_4->setText(QCoreApplication::translate("OrderForm", "\347\212\266\346\200\201", nullptr));
        ostate->setItemText(0, QCoreApplication::translate("OrderForm", "\345\234\250\350\264\255\347\211\251\350\275\246", nullptr));
        ostate->setItemText(1, QCoreApplication::translate("OrderForm", "\345\267\262\346\217\220\344\272\244", nullptr));
        ostate->setItemText(2, QCoreApplication::translate("OrderForm", "\345\267\262\345\256\214\346\210\220", nullptr));
        ostate->setItemText(3, QCoreApplication::translate("OrderForm", "\345\225\206\345\256\266\346\213\222\346\224\266", nullptr));
        ostate->setItemText(4, QCoreApplication::translate("OrderForm", "\347\224\250\346\210\267\345\210\240\351\231\244", nullptr));

        btn2->setText(QCoreApplication::translate("OrderForm", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderForm: public Ui_OrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERFORM_H
