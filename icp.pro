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
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Block/AbstractBlock.cpp \
    Port/Port.cpp \
    Block/BlocksFactory.cpp \
    Block/FillValuesBlock.cpp \
    Block/Blocks/Aadder1w1a2w1to1w1a2w2a3w3.cpp \
    Block/Blocks/Adder.cpp \
    Block/Blocks/Adder1w1a2w2a3w3to1w1a2w1.cpp \
    Block/Blocks/Adder1w2to1w1.cpp \
    Block/Blocks/Adder1w3to1w1a2w1.cpp \
    Block/Blocks/Divider.cpp \
    Block/Blocks/Multiplier.cpp \
    Block/Blocks/Round.cpp \
    Block/Blocks/Subtractor.cpp \
    Block/Blocks/WaterLaboratory.cpp \
    Type/AbstractType.cpp \
    Type/RegisterTypes.cpp \
    Type/Types/CarbonDioxide.cpp \
    Type/Types/Hydrogenium.cpp \
    Type/Types/Methan.cpp \
    Type/Types/OneDecimalNumber.cpp \
    Type/Types/Oxid.cpp \
    Type/Types/ThreeDecimalNumbers.cpp \
    Type/Types/TwoDecimalNumbers.cpp \
    Type/Types/Water.cpp \
    Port/FillValuesPort.cpp \
    Wire/Wire.cpp \
    Main.cpp \
    MainWindow.cpp


HEADERS += \
    Block/AbstractBlock.h \
    Port/Port.h \
    Block/BlocksFactory.h \
    Block/FillValuesBlock.h \
    Block/Blocks/Adder.h \
    Block/Blocks/Adder1w1a2w1to1w1a2w2a3w3.h \
    Block/Blocks/Adder1w1a2w2a3w3to1w1a2w1.h \
    Block/Blocks/Adder1w2to1w1.h \
    Block/Blocks/Adder1w3to1w1a2w1.h \
    Block/Blocks/Divider.h \
    Block/Blocks/Multiplier.h \
    Block/Blocks/Round.h \
    Block/Blocks/Subtractor.h \
    Block/Blocks/WaterLaboratory.h \
    Type/AbstractType.h \
    Type/RegisterTypes.h \
    Type/Types/CarbonDioxide.h \
    Type/Types/Hydrogenium.h \
    Type/Types/Methan.h \
    Type/Types/OneDecimalNumber.h \
    Type/Types/Oxid.h \
    Type/Types/ThreeDecimalNumbers.h \
    Type/Types/TwoDecimalNumbers.h \
    Type/Types/Water.h \
    Port/FillValuesPort.h \
    Wire/Wire.h \
    MainWindow.h

FORMS += \
    MainWindow.ui \
    FillValues.ui

QMAKE_CXXFLAGS += -std=gnu++14 \
    -Wno-expansion-to-defined

DISTFILES +=

RESOURCES += \
    Resources.qrc
