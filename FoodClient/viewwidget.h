#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QToolButton>
#include <QList>
namespace Ui {
    class ViewWidget;
}

class ViewWidget : public QWidget {
Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = nullptr);

    ~ViewWidget();

    QScrollArea *getContent();
    QToolButton* getBackBtn();
    QToolButton* getUpdateBtn();
    void setHint(const QString&hint);
    void updateContent(QList<QWidget*>&widgets);

private:
    Ui::ViewWidget *ui;
};

#endif // VIEWWIDGET_H
