#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T12:04:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dragdropexe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draggablerectitem.cpp

HEADERS  += mainwindow.h \
    draggablerectitem.h

FORMS    += mainwindow.ui
