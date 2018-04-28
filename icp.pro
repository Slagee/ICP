#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T19:07:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = icp
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
    Block/adder.cpp \
    Block/subtractor.cpp \
    Port/port.cpp \
    Wire/wire.cpp \
    Block/abstractBlock.cpp \
    Type/abstractType.cpp \
    Type/onedecimalnumber.cpp \
    Type/twodecimalnumbers.cpp \
    Type/threedecimalnumbers.cpp

HEADERS += \
        mainwindow.h \
    Block/adder.h \
    Block/subtractor.h \
    Port/port.h \
    Wire/wire.h \
    Block/abstractBlock.h \
    Type/abstractType.h \
    Type/onedecimalnumber.h \
    Type/twodecimalnumbers.h \
    Type/threedecimalnumbers.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS += -std=gnu++14

DISTFILES +=
