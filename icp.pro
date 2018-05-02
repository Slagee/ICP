#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T19:07:16
#
#-------------------------------------------------

QT       += core gui
QT       += xml

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
    Block/abstractBlock.cpp \
    Block/adder.cpp \
    Block/subtractor.cpp \
    Block/multiplier.cpp \
    Block/divider.cpp \
    Block/adder1w1a2w2a3w3to1w1a2w1.cpp \
    Block/adder1w1a2w1to1w1a2w2a3w3.cpp \
    Type/abstractType.cpp \
    Type/onedecimalnumber.cpp \
    Type/twodecimalnumbers.cpp \
    Type/threedecimalnumbers.cpp\
    Port/port.cpp \
    Wire/wire.cpp \
    values.cpp \
    Type/registrtypes.cpp \
    Block/blocksfactory.cpp \
    Block/fillvaluesblock.cpp


HEADERS += \
    mainwindow.h \
    Port/port.h \
    Block/abstractBlock.h \
    Block/adder.h \
    Block/subtractor.h \
    Block/multiplier.h \
    Block/divider.h \
    Block/adder1w1a2w2a3w3to1w1a2w1.h \
    Block/adder1w1a2w1to1w1a2w2a3w3.h \
    Type/abstractType.h \
    Type/onedecimalnumber.h \
    Type/twodecimalnumbers.h \
    Type/threedecimalnumbers.h \
    Wire/wire.h \
    Type/registrtypes.h \
    Block/blocksfactory.h \
    Block/fillvaluesblock.h

FORMS += \
        mainwindow.ui \
    values.ui

QMAKE_CXXFLAGS += -std=gnu++14

DISTFILES +=

RESOURCES += \
    resources.qrc
