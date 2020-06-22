QT       += core sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db.cpp \
    foodserver.cpp \
    main.cpp \
    net.cpp \
    order.cpp \
    product.cpp \
    user.cpp

HEADERS += \
    config.h \
    db.h \
    discount.h \
    foodserver.h \
    net.h \
    order.h \
    product.h \
    user.h

FORMS += 

msvc {
    # RC_ICONS = img/win.ico
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
