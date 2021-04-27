
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comboboxdelegate.cpp \
    comboboxfordb.cpp \
    dbworking.cpp \
    edit.cpp \
    filelog.cpp \
    filetablemodel.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    upgradedmodel.cpp

HEADERS += \
    Enumexec.h \
    comboboxdelegate.h \
    comboboxfordb.h \
    dbworking.h \
    edit.h \
    filelog.h \
    filetablemodel.h \
    logger.h \
    mainwindow.h \
    upgradedmodel.h

FORMS += \
    edit.ui \
    filelog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
