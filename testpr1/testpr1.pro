
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DAT.cpp \
    comboboxdelegate.cpp \
    comboboxfordb.cpp \
    dbworking.cpp \
    edit.cpp \
    filelog.cpp \
    filetablemodel.cpp \
    help.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    upgradedmodel.cpp

HEADERS += \
    DAT.h \
    comboboxdelegate.h \
    comboboxfordb.h \
    dbworking.h \
    edit.h \
    filelog.h \
    filetablemodel.h \
    help.h \
    logger.h \
    mainwindow.h \
    upgradedmodel.h

FORMS += \
    edit.ui \
    filelog.ui \
    help.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

VERSION=2.3.0.0
QMAKE_TARGET_COMPANY=Central Scientific Research Radiotechnical Institute name of the academician A.I. Berg
QMAKE_TARGET_PRODUCT=Graduation project Zhilyaeva A.A.
QMAKE_TARGET_DESCRIPTION=Database application
QMAKE_TARGET_COPYRIGHT=(с) Anastasiya Zhilyaeva

RC_ICONS="table.ico"
