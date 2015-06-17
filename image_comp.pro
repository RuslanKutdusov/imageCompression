#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T23:32:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_comp
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
LIBS += -lz

SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    jpeg.cpp \
    wavelet.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    jpeg.h \
    wavelet.h \
    ycbcr.h \
    utils.h

FORMS    += mainwindow.ui
