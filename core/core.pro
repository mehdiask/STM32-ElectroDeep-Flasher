QT += core serialport

TEMPLATE = lib
CONFIG += staticlib c++11

TARGET = Core
DESTDIR = $$PWD/../libs

SOURCES += \
    STM32Bootloader.cpp \
    MessageColors.cpp

HEADERS += \
    STM32Bootloader.h \
    MessageColors.h
