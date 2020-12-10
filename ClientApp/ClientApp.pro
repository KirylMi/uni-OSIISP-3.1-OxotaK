QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db.cpp \
    dbparser.cpp \
    drink.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    models.cpp \
    regwindow.cpp \
    user.cpp \
    utils.cpp \
    windowadd.cpp \
    windowedit.cpp

HEADERS += \
    db.h \
    dbparser.h \
    drink.h \
    loginwindow.h \
    mainwindow.h \
    models.h \
    regwindow.h \
    user.h \
    utils.h \
    windowadd.h \
    windowedit.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    regwindow.ui \
    windowadd.ui \
    windowedit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
