#-------------------------------------------------
#
# Project created by QtCreator 2013-09-07T20:36:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = alvertor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    resource.qrc
QMAKE_LFLAGS += -static-libgcc
