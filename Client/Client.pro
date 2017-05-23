TEMPLATE = app

QT += qml quick
QT += network
CONFIG += c++11

SOURCES += main.cpp \
    clientnetworkinterface.cpp \
    spliter.cpp \
    dollarspliter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    clientnetworkinterface.h \
    spliter.h \
    dollarspliter.h
