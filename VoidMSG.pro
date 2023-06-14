QT       += core gui
QT          +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api.cpp \
    loginpage.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    refresherDirect.cpp \
    refresherabstract.cpp \
    refresherchannel.cpp \
    refreshergroup.cpp \
    registerpage.cpp \
    user.cpp

HEADERS += \
    api.h \
    loginpage.h \
    mainwindow.h \
    message.h \
    refresherDirect.h \
    refresherabstract.h \
    refresherchannel.h \
    refreshergroup.h \
    registerpage.h \
    user.h

FORMS += \
    loginpage.ui \
    mainwindow.ui \
    registerpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Styles.qrc
