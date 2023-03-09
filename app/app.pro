#-------------------------------------------------
#
# Project created by QtCreator 2023-02-10T19:24:12
#
#-------------------------------------------------

QT       += core
QT -=gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
include(/home/fabien/Documents/FDS/M1/TER/opencv-4.7.0/opencv.pri)
