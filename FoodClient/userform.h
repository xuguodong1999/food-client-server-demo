#ifndef USERFORM_H
#define USERFORM_H

#include <QWidget>
#include <QToolButton>
#include "user.h"

namespace Ui {
    class UserForm;
}

class UserForm : public QWidget {
Q_OBJECT

public:
    explicit UserForm(QWidget *parent = nullptr);

    ~UserForm();

    User getUser();

    void update(const User &user);

    QToolButton *getLogin();

    QToolButton *getRegister();

private:
    Ui::UserForm *ui;
};

#endif // USERFORM_H
