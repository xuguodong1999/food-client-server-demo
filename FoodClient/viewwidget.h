#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QToolButton>
#include <QList>
#include "user.h"

namespace Ui {
    class ViewWidget;
}

class ViewWidget : public QWidget {
Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = nullptr);

    ~ViewWidget();

    QScrollArea *getContent();

    QToolButton *getBackBtn();

    QToolButton *getUpdateBtn();

    void setUinfo(const User &user);

    void setHint(const QString &hint);

    void updateContent(QList<QWidget *> &widgets);

private:
    Ui::ViewWidget *ui;
};

#endif // VIEWWIDGET_H
