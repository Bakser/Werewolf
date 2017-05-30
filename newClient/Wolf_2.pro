#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T15:33:30
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wolf_2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    night.cpp \
    newroom.cpp \
    joinroom.cpp \
    drawcard.cpp \
    waitroom.cpp \
    globals.cpp \
    mainwindowplay.cpp \
    handle1.cpp \
    vote.cpp \
    chat.cpp \
    clientnetworkinterface.cpp \
    eventhandler.cpp \
    stringoperate.cpp

HEADERS  += mainwindow.h \
    night.h \
    newroom.h \
    joinroom.h \
    drawcard.h \
    waitroom.h \
    globals.h \
    mainwindowplay.h \
    vote.h \
    chat.h \
    clientnetworkinterface.h \
    eventhandler.h \
    stringoperate.h

FORMS    += mainwindow.ui \
    night.ui \
    newroom.ui \
    joinroom.ui \
    drawcard.ui \
    waitroom.ui \
    vote.ui \
    chat.ui

DISTFILES += \
    UI/_cupido.jpg \
    UI/_elder.jpg \
    UI/_foresee.jpg \
    UI/_girl.jpg \
    UI/_guard.jpg \
    UI/_hunter.jpg \
    UI/_piper.jpg \
    UI/_scapegoat.jpg \
    UI/_sheriff.jpg \
    UI/_thief.jpg \
    UI/_villager.jpg \
    UI/_witch.jpg \
    UI/_wolf.jpg \
    UI/background.jpeg \
    UI/icon.jpg \
    UI/main.jpg \
    UI/day.jpg \
    UI/lose.jpg

RESOURCES += \
    picture.qrc
