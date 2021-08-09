TEMPLATE = app
CONFIG += console c++11
CONFIG += resources_big
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Exception.cpp \
    object.cpp

HEADERS += \
    SmartPointer.h \
    Exception.h \
    object.h \
    list.h \
    array.h \
    StaticArray.h \
    SeqList.h \
    StaticList.h \
    DynamicList.h \
    DynamiCarray.h
