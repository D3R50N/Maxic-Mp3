#-------------------------------------------------
#
# Project created by QtCreator 2021-07-07T19:32:41
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MaxcMp3
TEMPLATE = app


SOURCES += main.cpp\
        mainmenu.cpp \
    home.cpp \
    local.cpp \
    record.cpp \
    settings.cpp

HEADERS  += mainmenu.h \
    home.h \
    local.h \
    all.h \
    record.h \
    settings.h

FORMS    += mainmenu.ui \
    home.ui \
    local.ui \
    record.ui \
    settings.ui

RESOURCES += \
    icones.qrc
