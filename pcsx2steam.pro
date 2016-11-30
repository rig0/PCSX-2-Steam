#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T09:22:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PCSX-2-Steam
TEMPLATE = app


SOURCES += main.cpp\
        pcsx2steam.cpp

HEADERS  += pcsx2steam.h

FORMS    += pcsx2steam.ui

RC_ICONS = pcsx2s.ico

VERSION = 1.0.0.1

QMAKE_TARGET_COMPANY = RAMBO
QMAKE_TARGET_PRODUCT = PCSX 2 Steam
QMAKE_TARGET_DESCRIPTION = PCSX 2 Steam
QMAKE_TARGET_COPYRIGHT = RAMBO

RESOURCES += \
    res.qrc
