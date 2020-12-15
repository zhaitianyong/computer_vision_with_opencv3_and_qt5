#-------------------------------------------------
#
# Project created by QtCreator 2019-11-29T12:43:12
#
#-------------------------------------------------

QT       += widgets

TARGET = filter_plugin
TEMPLATE = lib

DEFINES += FILTER_PLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        filter_plugin.cpp

HEADERS += \
        filter_plugin.h \
        filter_plugin_global.h  
FORMS += \
    plugin.ui


unix {
    target.path = /usr/lib
    INSTALLS += target
}
win32:
{
    CONFIG(debug, debug|release){
        DESTDIR =$$PWD/../../bin/debug/plugins
    }else{
        DESTDIR =$$PWD/../../bin/release/plugins
    }
}

# opencv
include($$PWD/../../3rdparty/opencv410.pri)

INCLUDEPATH += $$PWD/../../3rdparty


