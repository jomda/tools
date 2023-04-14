#-------------------------------------------------
#
# Project created by QtCreator 2018-09-04T15:09:51
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FoundManager
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

# include path
INCLUDEPATH += . \
               ./SQL \
               ./Trade

# dependancy path
DEPENDPATH += . \
              ./SQL \
              ./Trade


SOURCES += main.cpp\
        MainWindow.cpp \
        SQLConfig.cpp \
        sell.cpp

HEADERS  += MainWindow.h \
            SQLConfig.h \
            sell.h

# destination directory to store excutable files
DESTDIR = $$PWD/target
