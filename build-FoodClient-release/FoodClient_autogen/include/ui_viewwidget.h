/********************************************************************************
** Form generated from reading UI file 'viewwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWWIDGET_H
#define UI_VIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewWidget
{
public:
    QLabel *userinfo;
    QLabel *hint;
    QScrollArea *scrollArea;
    QWidget *content;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *back;
    QToolButton *update;
    QLabel *uinfo;

    void setupUi(QWidget *ViewWidget)
    {
        if (ViewWidget->objectName().isEmpty())
            ViewWidget->setObjectName(QString::fromUtf8("ViewWidget"));
        ViewWidget->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ViewWidget->sizePolicy().hasHeightForWidth());
        ViewWidget->setSizePolicy(sizePolicy);
        userinfo = new QLabel(ViewWidget);
        userinfo->setObjectName(QString::fromUtf8("userinfo"));
        userinfo->setGeometry(QRect(0, 0, 200, 50));
        userinfo->setAlignment(Qt::AlignCenter);
        hint = new QLabel(ViewWidget);
        hint->setObjectName(QString::fromUtf8("hint"));
        hint->setGeometry(QRect(760, 0, 200, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        hint->setFont(font);
        hint->setAlignment(Qt::AlignCenter);
        scrollArea = new QScrollArea(ViewWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 70, 941, 461));
        scrollArea->setWidgetResizable(true);
        content = new QWidget();
        content->setObjectName(QString::fromUtf8("content"));
        content->setGeometry(QRect(0, 0, 939, 459));
        scrollArea->setWidget(content);
        layoutWidget = new QWidget(ViewWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(220, 0, 521, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        back = new QToolButton(layoutWidget);
        back->setObjectName(QString::fromUtf8("back"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy1);
        back->setFont(font);

        horizontalLayout->addWidget(back);

        update = new QToolButton(layoutWidget);
        update->setObjectName(QString::fromUtf8("update"));
        sizePolicy1.setHeightForWidth(update->sizePolicy().hasHeightForWidth());
        update->setSizePolicy(sizePolicy1);
        update->setFont(font);

        horizontalLayout->addWidget(update);

        uinfo = new QLabel(ViewWidget);
        uinfo->setObjectName(QString::fromUtf8("uinfo"));
        uinfo->setGeometry(QRect(0, 0, 200, 70));
        uinfo->setFont(font);
        uinfo->setAlignment(Qt::AlignCenter);

        retranslateUi(ViewWidget);

        QMetaObject::connectSlotsByName(ViewWidget);
    } // setupUi

    void retranslateUi(QWidget *ViewWidget)
    {
        ViewWidget->setWindowTitle(QCoreApplication::translate("ViewWidget", "Form", nullptr));
        userinfo->setText(QString());
        hint->setText(QCoreApplication::translate("ViewWidget", "\347\225\214\351\235\242\344\277\241\346\201\257", nullptr));
        back->setText(QCoreApplication::translate("ViewWidget", "\350\277\224\345\233\236", nullptr));
        update->setText(QCoreApplication::translate("ViewWidget", "\345\210\267\346\226\260", nullptr));
        uinfo->setText(QCoreApplication::translate("ViewWidget", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewWidget: public Ui_ViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWWIDGET_H
