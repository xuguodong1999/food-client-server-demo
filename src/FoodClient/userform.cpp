#include "userform.h"
#include "ui_userform.h"
#include <QBuffer>
#include <QFileDialog>

UserForm::UserForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::UserForm) {
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->photo->setIcon(QIcon(QPixmap(":/default_people.png").scaled(200, 200)));
    connect(ui->photo, &QToolButton::clicked, [=]() {
        QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                qApp->applicationDirPath(),
                "Image files(*.bmp *.jpg *.png)"
        );
        if (!fileName.isEmpty())
            ui->photo->setIcon(QIcon(fileName));

    });
    connect(ui->utype, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int value) {
        if (value == 2) {//不允许注册管理员账号
            ui->btn2->setDisabled(true);
        } else {
            ui->btn2->setEnabled(true);
        }
    });

}

UserForm::~UserForm() {
    delete ui;
}

User UserForm::getUser() {
    User user;
    user.setUid(-1);
    user.setUtype(Utype(ui->utype->currentIndex()));
    user.setUname(ui->uname->text());
    user.setPassword(ui->password->text());
    QByteArray imageData;
    QBuffer buffer(&imageData);
    ui->photo->icon().pixmap(200, 200).save(&buffer, "jpg");
    user.setPhoto(imageData.toBase64());
    return user;
}

void UserForm::update(const User &user) {
    ui->utype->setCurrentIndex(user.getUtype());
    ui->uname->setText(user.getUname());
    QByteArray imageData = QByteArray::fromBase64(user.getPhoto().toLatin1());
    QPixmap image;
    image.loadFromData(imageData);
    ui->photo->setIcon(QIcon(image));
}

QToolButton *UserForm::getLogin() {
    return ui->btn1;
}

QToolButton *UserForm::getRegister() {
    return ui->btn2;
}
