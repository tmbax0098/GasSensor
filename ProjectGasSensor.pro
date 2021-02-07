QT       += core gui charts serialport sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutwindow.cpp \
    exportwindow.cpp \
    keyboardwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    messagewindow.cpp \
    nodesetting.cpp \
    nodewindow.cpp \
    packet.cpp \
    passwordcertificatewindow.cpp \
    portmanager.cpp \
    settingnodewindow.cpp \
    settingpasswordwindow.cpp \
    settingportwindow.cpp \
    settingtimewindow.cpp \
    settingwindow.cpp

HEADERS += \
    aboutwindow.h \
    exportwindow.h \
    keyboardwindow.h \
    mainwindow.h \
    messagewindow.h \
    nodesetting.h \
    nodewindow.h \
    packet.h \
    passwordcertificatewindow.h \
    portmanager.h \
    settingnodewindow.h \
    settingpasswordwindow.h \
    settingportwindow.h \
    settingtimewindow.h \
    settingwindow.h

FORMS += \
    aboutwindow.ui \
    exportwindow.ui \
    keyboardwindow.ui \
    mainwindow.ui \
    messagewindow.ui \
    nodewindow.ui \
    passwordcertificatewindow.ui \
    settingnodewindow.ui \
    settingpasswordwindow.ui \
    settingportwindow.ui \
    settingtimewindow.ui \
    settingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    public.qrc
