#-------------------------------------------------
#
# Project created by QtCreator 2017-05-22T15:02:51
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    servernetworkinterface.cpp \
    eventhandler.cpp \
    spliter.cpp \
    clientstatus.cpp \
    dollarspliter.cpp \
    naivehandler.cpp

HEADERS  += maindialog.h \
    servernetworkinterface.h \
    eventhandler.h \
    spliter.h \
    clientstatus.h \
    dollarspliter.h \
    naivehandler.h

FORMS    += maindialog.ui
