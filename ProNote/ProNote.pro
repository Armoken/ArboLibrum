#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T15:02:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProNote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    readorg.cpp \
    writeorg.cpp \
    encoding.cpp \
    decoding.cpp \
    decompression.cpp \
    note.cpp \
    compression.cpp

HEADERS  += mainwindow.h \
    readorg.h \
    writeorg.h \
    encoding.h \
    decoding.h \
    decompression.h \
    note.h \
    compression.h

FORMS    += mainwindow.ui
