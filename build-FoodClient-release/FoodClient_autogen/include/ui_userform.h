/********************************************************************************
** Form generated from reading UI file 'userform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERFORM_H
#define UI_USERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserForm
{
public:
    QToolButton *photo;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *password;
    QToolButton *btn1;
    QToolButton *btn2;
    QLabel *label_5;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *uname;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *utype;
    QLabel *label_6;

    void setupUi(QWidget *UserForm)
    {
        if (UserForm->objectName().isEmpty())
            UserForm->setObjectName(QString::fromUtf8("UserForm"));
        UserForm->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UserForm->sizePolicy().hasHeightForWidth());
        UserForm->setSizePolicy(sizePolicy);
        photo = new QToolButton(UserForm);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(150, 200, 200, 200));
        photo->setMinimumSize(QSize(200, 200));
        photo->setMaximumSize(QSize(200, 200));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        photo->setFont(font);
        photo->setIconSize(QSize(200, 200));
        layoutWidget = new QWidget(UserForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(430, 220, 351, 71));
        layoutWidget->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, 10, 10, 10);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        password = new QLineEdit(layoutWidget);
        password->setObjectName(QString::fromUtf8("password"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(password->sizePolicy().hasHeightForWidth());
        password->setSizePolicy(sizePolicy1);
        password->setFont(font);

        horizontalLayout_3->addWidget(password);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);
        btn1 = new QToolButton(UserForm);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(430, 430, 150, 60));
        btn1->setFont(font1);
        btn2 = new QToolButton(UserForm);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(630, 430, 150, 60));
        btn2->setFont(font1);
        label_5 = new QLabel(UserForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(220, 0, 491, 101));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(30);
        font2.setBold(false);
        font2.setWeight(50);
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);
        layoutWidget1 = new QWidget(UserForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(430, 120, 351, 61));
        layoutWidget1->setFont(font);
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        uname = new QLineEdit(layoutWidget1);
        uname->setObjectName(QString::fromUtf8("uname"));
        sizePolicy1.setHeightForWidth(uname->sizePolicy().hasHeightForWidth());
        uname->setSizePolicy(sizePolicy1);
        uname->setFont(font);

        horizontalLayout->addWidget(uname);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);
        layoutWidget2 = new QWidget(UserForm);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(430, 330, 351, 71));
        layoutWidget2->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 10, 10, 10);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        utype = new QComboBox(layoutWidget2);
        utype->addItem(QString());
        utype->addItem(QString());
        utype->addItem(QString());
        utype->setObjectName(QString::fromUtf8("utype"));
        sizePolicy1.setHeightForWidth(utype->sizePolicy().hasHeightForWidth());
        utype->setSizePolicy(sizePolicy1);
        utype->setFont(font);

        horizontalLayout_2->addWidget(utype);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);
        label_6 = new QLabel(UserForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(100, 100, 291, 81));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(18);
        font3.setBold(false);
        font3.setWeight(50);
        label_6->setFont(font3);
        label_6->setAlignment(Qt::AlignCenter);

        retranslateUi(UserForm);

        QMetaObject::connectSlotsByName(UserForm);
    } // setupUi

    void retranslateUi(QWidget *UserForm)
    {
        UserForm->setWindowTitle(QCoreApplication::translate("UserForm", "Form", nullptr));
        photo->setText(QCoreApplication::translate("UserForm", "\345\244\264\345\203\217", nullptr));
        label_3->setText(QCoreApplication::translate("UserForm", "\345\257\206\347\240\201", nullptr));
        btn1->setText(QCoreApplication::translate("UserForm", "\347\231\273\345\275\225", nullptr));
        btn2->setText(QCoreApplication::translate("UserForm", "\346\263\250\345\206\214", nullptr));
        label_5->setText(QCoreApplication::translate("UserForm", "\345\244\226\345\215\226\344\272\244\346\230\223\345\271\263\345\217\260", nullptr));
        label->setText(QCoreApplication::translate("UserForm", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("UserForm", "\347\224\250\346\210\267\347\261\273\345\236\213", nullptr));
        utype->setItemText(0, QCoreApplication::translate("UserForm", "\345\225\206\345\256\266", nullptr));
        utype->setItemText(1, QCoreApplication::translate("UserForm", "\350\256\242\351\244\220\350\200\205", nullptr));
        utype->setItemText(2, QCoreApplication::translate("UserForm", "\347\256\241\347\220\206\345\221\230", nullptr));

        label_6->setText(QCoreApplication::translate("UserForm", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserForm: public Ui_UserForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERFORM_H
