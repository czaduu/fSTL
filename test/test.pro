include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11 c++14 c++1z
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_test_inz.h

SOURCES += \
        main.cpp
