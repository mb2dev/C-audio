TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../app
HEADERS         = fxplugin.h
SOURCES         = fxplugin.cpp
TARGET          = $$qtLibraryTarget(audiomixer)
DESTDIR         = ../plugins
