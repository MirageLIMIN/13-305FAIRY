#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T15:10:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    onebox.cpp

HEADERS  += widget.h \
    onebox.h

FORMS    += widget.ui

RESOURCES += \
    2048.qrc
