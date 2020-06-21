/********************************************************************************
** Form generated from reading UI file 'usertodoform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERTODOFORM_H
#define UI_USERTODOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserTodoForm
{
public:
    QLabel *hint;
    QLabel *uinfo;
    QToolButton *btn1;
    QToolButton *btn2;

    void setupUi(QWidget *UserTodoForm)
    {
        if (UserTodoForm->objectName().isEmpty())
            UserTodoForm->setObjectName(QString::fromUtf8("UserTodoForm"));
        UserTodoForm->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UserTodoForm->sizePolicy().hasHeightForWidth());
        UserTodoForm->setSizePolicy(sizePolicy);
        hint = new QLabel(UserTodoForm);
        hint->setObjectName(QString::fromUtf8("hint"));
        hint->setGeometry(QRect(560, 0, 400, 80));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(18);
        font.setBold(false);
        font.setWeight(50);
        hint->setFont(font);
        hint->setAlignment(Qt::AlignCenter);
        uinfo = new QLabel(UserTodoForm);
        uinfo->setObjectName(QString::fromUtf8("uinfo"));
        uinfo->setGeometry(QRect(0, 0, 400, 80));
        uinfo->setFont(font);
        uinfo->setAlignment(Qt::AlignCenter);
        btn1 = new QToolButton(UserTodoForm);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(130, 190, 300, 186));
        btn1->setMinimumSize(QSize(0, 0));
        btn1->setMaximumSize(QSize(10000, 10000));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setWeight(75);
        btn1->setFont(font1);
        btn1->setIconSize(QSize(100, 100));
        btn2 = new QToolButton(UserTodoForm);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(530, 190, 300, 186));
        btn2->setMinimumSize(QSize(0, 0));
        btn2->setMaximumSize(QSize(10000, 10000));
        btn2->setFont(font1);
        btn2->setIconSize(QSize(100, 100));

        retranslateUi(UserTodoForm);

        QMetaObject::connectSlotsByName(UserTodoForm);
    } // setupUi

    void retranslateUi(QWidget *UserTodoForm)
    {
        UserTodoForm->setWindowTitle(QCoreApplication::translate("UserTodoForm", "Form", nullptr));
        hint->setText(QCoreApplication::translate("UserTodoForm", "\350\276\223\345\205\245\346\217\220\347\244\272\346\240\267\345\274\217", nullptr));
        uinfo->setText(QCoreApplication::translate("UserTodoForm", "\350\276\223\345\205\245\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        btn1->setText(QCoreApplication::translate("UserTodoForm", "\345\212\237\350\203\2751", nullptr));
        btn2->setText(QCoreApplication::translate("UserTodoForm", "\345\212\237\350\203\2752", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserTodoForm: public Ui_UserTodoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERTODOFORM_H
