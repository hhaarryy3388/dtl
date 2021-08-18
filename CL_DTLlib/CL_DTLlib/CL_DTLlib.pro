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
    StaticArray.h \
    SeqList.h \
    StaticList.h \
    DynamicList.h \
    DynamiCarray.h \
    Object.h \
    LinkList.h \
    List.h \
    StaticLinkList.h \
    Pointer.h \
    SharedPointer.h \
    Array.h \
    CircleLinkList.h
