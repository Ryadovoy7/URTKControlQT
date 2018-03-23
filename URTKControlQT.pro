#-------------------------------------------------
#
# Project created by QtCreator 2018-01-25T09:23:27
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += widgets


QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01

DEFINES += _ATL_XP_TARGETING
QMAKE_CFLAGS += /D _USING_V140_SDK71_
QMAKE_CXXFLAGS += /D _USING_V140_SDK71_
LIBS *= -L”%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Lib”
INCLUDEPATH += “%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Include”


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = URTKControlQT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Algorithm.cpp \
    port.cpp \
    operation.cpp \
    move.cpp \
    grab.cpp \
    calibr.cpp \
    test.cpp \
    flag.cpp \
    check.cpp \
    urtkserver.cpp \
    settings.cpp

HEADERS += \
        mainwindow.h \
    Const.h \
    Algorithm.h \
    port.h \
    operation.h \
    move.h \
    grab.h \
    calibr.h \
    test.h \
    flag.h \
    check.h \
    urtkserver.h \
    settings.h

FORMS += \
        mainwindow.ui \
    scriptwindow.ui \
    settings.ui

DISTFILES += \

LIBS += -L$$PWD/lib/ -linpout32

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include
