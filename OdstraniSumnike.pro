#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T13:57:10
#
#-------------------------------------------------

QT       += core gui

TARGET = "Popravi podnapise"
TEMPLATE = app

win32:RC_FILE += PopraviPodnapise.rc


SOURCES += main.cpp\
        popravipodnapise.cpp \
    popravljalec.cpp

HEADERS  += popravipodnapise.h \
    popravljalec.h

FORMS    += popravipodnapise.ui

OTHER_FILES += \
    PopraviPodnapise.rc
