#ifndef TODOFORM_H
#define TODOFORM_H

#include "user.h"
#include <QLabel>
#include <QWidget>
#include <QToolButton>

namespace Ui {
    class TodoForm;
}
class TodoForm : public QWidget {
Q_OBJECT
public:
    explicit TodoForm(QWidget *parent = nullptr);

    ~TodoForm();

    void setUser(const User &user);

    QToolButton *getBtn1();

    QToolButton *getBtn2();

    QLabel *getHint();

    QLabel *getUinfo();

private:
    Ui::TodoForm *ui;
};

class TodoFormBuilder {
public:
    TodoFormBuilder();

    virtual void buildUserInfo(const User &user) = 0;

    virtual void buildBtn1() = 0;

    virtual void buildBtn2() = 0;

    TodoForm *createTodoForm();

protected:
    TodoForm *userTodoForm;
};

class BuyerTodoBuilder : public TodoFormBuilder {
public:
    void buildUserInfo(const User &user) override;

    void buildBtn1() override;

    void buildBtn2() override;
};

class SellerTodoBuilder : public TodoFormBuilder {
public:
    void buildUserInfo(const User &user) override;

    void buildBtn1() override;

    void buildBtn2() override;
};

class AdminTodoBuilder : public TodoFormBuilder {
public:
    void buildUserInfo(const User &user) override;

    void buildBtn1() override;

    void buildBtn2() override;
};

class TodoFormController {
public:
    TodoForm *createUserTodoForm(TodoFormBuilder *todoBuilder, const User &user);
};

#endif // TODOFORM_H
