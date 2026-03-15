QT += core serialport

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app
TARGET = cli_app

LIBS += -L$$PWD/../libs/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

SOURCES += main.cpp
HEADERS +=
