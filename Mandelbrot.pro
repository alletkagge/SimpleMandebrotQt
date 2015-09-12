#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T21:26:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mandelbrot
TEMPLATE = app

QMAKE_CXXFLAGS += -O3 -fopenmp
QMAKE_LFLAGS += -fopenmp

SOURCES += main.cpp\
        mainwindow.cpp \
    mandelbrot.cpp \
    mandelbrotthread.cpp

HEADERS  += mainwindow.h \
    complexnumber.h \
    mandelbrot.h \
    mandelbrotthread.h

FORMS    += mainwindow.ui
