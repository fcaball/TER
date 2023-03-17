#-------------------------------------------------
#
# Project created by QtCreator 2023-02-10T19:24:12
#
#-------------------------------------------------

QT       += core
QT -=gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
CONFIG -= app_bundle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    images.cpp

HEADERS  += mainwindow.h \
    images.h

FORMS    += mainwindow.ui
include(/home/fabien/Documents/FDS/M1/TER/TER/opencv-4.7.0/opencv.pri)
