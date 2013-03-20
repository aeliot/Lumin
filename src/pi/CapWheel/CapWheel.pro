#-------------------------------------------------
#
# Project created by QtCreator 2013-03-10T17:58:31
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = CapWheel
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

SOURCES += \
    ../arduPi/arduPi.cpp

HEADERS += \
    ../arduPi/arduPi.h

SOURCES += \
    ../MPR121/mpr121.cpp

HEADERS += \
    ../MPR121/mpr121.h
