#ifndef USERTODOFORM_H
#define USERTODOFORM_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include "user.h"
namespace Ui {
    class UserTodoForm;
}

class UserTodoForm : public QWidget {
Q_OBJECT

public:
    explicit UserTodoForm(QWidget *parent = nullptr);

    ~UserTodoForm();

    QLabel *getHint();
    QLabel *getUinfo();
    QToolButton*getBtn1();
    QToolButton*getBtn2();
    void setUser(const User&user);
private:
    Ui::UserTodoForm *ui;
};
class UserTodoBuilder {
public:
    UserTodoBuilder();
    virtual void buildUserInfo(const User&user) = 0;

    virtual void buildBtn1() = 0;

    virtual void buildBtn2() = 0;
    UserTodoForm* createTodoForm();
protected:
    UserTodoForm*userTodoForm;
};

class BuyerTodoBuilder : public UserTodoBuilder {
public:
    void buildUserInfo(const User&user)override ;
    void buildBtn1() override ;
    void buildBtn2()override ;
};
class SellerTodoBuilder : public UserTodoBuilder {
public:
    void buildUserInfo(const User&user)override ;
    void buildBtn1() override ;
    void buildBtn2()override ;
};
class AdminTodoBuilder : public UserTodoBuilder {
public:
    void buildUserInfo(const User&user)override ;
    void buildBtn1() override ;
    void buildBtn2()override ;
};
class TodoFormController{
public:
    UserTodoForm*createUserTodoForm(UserTodoBuilder*todoBuilder,const User&user);
};
#endif // USERTODOFORM_H
