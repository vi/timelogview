#-------------------------------------------------
#
# Project created by QtCreator 2014-01-26T16:23:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timelogview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    mylistmodel.cpp \
    myitemselectionmodel.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    logentry.h \
    mylistmodel.h \
    myitemselectionmodel.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../src/p \
    GPL.txt \
    input.txt
