#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T17:03:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TileMapperLite
TEMPLATE = app

QMAKE_CXXFLAGS += -static-libgcc

SOURCES += main.cpp\
    MainWindow.cpp \
    graphics_views/MapGraphicsView.cpp \
    graphics_views/TileGraphicsView.cpp \
    graphics_views/TilesetGraphicsView.cpp \
    dialogs/MapSizeDialog.cpp \
    models/map.cpp

HEADERS  += \
    map.h \
    MainWindow.h \
    graphics_views/MapGraphicsView.h \
    graphics_views/TileGraphicsView.h \
    graphics_views/TilesetGraphicsView.h \
    dialogs/MapSizeDialog.h \
    models/map.h

FORMS    += \
    ui/MainWindow.ui \
    ui/MapSizeDialog.ui

RESOURCES += \
    Ressource/RessourceIcon.qrc

OTHER_FILES += \
    icon.ico \
    icone.rc


DISTFILES +=




