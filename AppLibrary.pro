TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    capplibrary.cpp \
    appmenu.cpp \
    define.cpp \
    cdatafile.cpp \
    cappitems.cpp

HEADERS += \
    capplibrary.h \
    appmenu.h \
    define.h \
    cdatafile.h \
    cappitems.h \
    cappitems.hpp
