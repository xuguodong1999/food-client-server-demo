#include "productform.h"
#include "ui_productform.h"
#include <QBuffer>
#include <QFileDialog>

ProductForm::ProductForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ProductForm), isSellerForm(true) {
    ui->setupUi(this);
    ui->photo->setIcon(QIcon(QPixmap(":/default_food.jpg").scaled(200, 200)));
    connect(ui->photo, &QToolButton::clicked, [=]() {
        if (!isSellerForm)return;
        QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                qApp->applicationDirPath(),
                "Image files(*.bmp *.jpg *.png)"
        );
        if (!fileName.isEmpty())
            ui->photo->setIcon(QPixmap(fileName).scaled(200, 200));
    });
}

ProductForm::~ProductForm() {
    delete ui;
}

QToolButton *ProductForm::getPhotoBtn() {
    return ui->photo;
}

QToolButton *ProductForm::getFuncBtn() {
    return ui->btn;
}

QLineEdit *ProductForm::getUnameEdit() {
    return ui->uname;
}

QLineEdit *ProductForm::getPnameEdit() {
    return ui->pname;
}

QLineEdit *ProductForm::getPinfoEdit() {
    return ui->pinfo;
}

QDoubleSpinBox *ProductForm::getPriceBox() {
    return ui->price;
}

QComboBox *ProductForm::getPstateBox() {
    return ui->pstate;
}

void ProductForm::setProduct(const Product &product) {
    p = product;
    getUnameEdit()->setText(QString::number(p.getUid()));
    getPnameEdit()->setText(p.getPname());
    getPinfoEdit()->setText(p.getPinfo());
    getPriceBox()->setValue(p.getPrice());
    getPstateBox()->setCurrentIndex(p.getPstate());
    QByteArray imageData = QByteArray::fromBase64(p.getPhoto().toLatin1());
    QPixmap image;
    image.loadFromData(imageData);
    ui->photo->setIcon(QIcon(image));
}

Product ProductForm::getProduct() {
    p.setPrice(getPriceBox()->value());
    p.setPstate(Pstate(getPstateBox()->currentIndex()));
    p.setPinfo(getPinfoEdit()->text());
    p.setPname(getPnameEdit()->text());
    QByteArray imageData;
    QBuffer buffer(&imageData);
    ui->photo->icon().pixmap(200, 200).save(&buffer, "jpg");
    p.setPhoto(imageData.toBase64());
    return p;
}

void ProductForm::setDisplayOnly() {
    ui->unameLabel->setText("商家编号");
    isSellerForm = false;
    getFuncBtn()->setText("选择");
    getUnameEdit()->setFocusPolicy(Qt::NoFocus);
    getPnameEdit()->setFocusPolicy(Qt::NoFocus);
    getPinfoEdit()->setFocusPolicy(Qt::NoFocus);
    getPriceBox()->setDisabled(true);
    getPstateBox()->setDisabled(true);
    if (getPstateBox()->currentIndex() == 1) {
        getFuncBtn()->setDisabled(true);
    }
}



