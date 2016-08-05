#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T11:55:53
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = infrapunatutka
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    pictures.qrc
