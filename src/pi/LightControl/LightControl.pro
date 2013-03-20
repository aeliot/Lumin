#-------------------------------------------------
#
# Project created by QtCreator 2013-03-10T04:27:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LightControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

HEADERS += \
    ../arduPi/arduPi.h

SOURCES += \
    ../arduPi/arduPi.cpp

HEADERS += \
    ../MPR121/mpr121.h

SOURCES += \
    ../MPR121/mpr121.cpp

HEADERS += \
    ../stripper/stripper.h

SOURCES += \
    ../stripper/stripper.cpp

HEADERS += \
    wheel.h

SOURCES += \
    wheel.cpp
