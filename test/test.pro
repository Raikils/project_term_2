QT += testlib
QT += gui
QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../"Films for you"

HEADERS += \
    ../"Films for you"/film.h \
    ../"Films for you"/profile.h \
    ../"Films for you"/rapidapikey.h


SOURCES += \
    tst_test.cpp \
    ../"Films for you"/film.cpp \
    ../"Films for you"/profile.cpp \
    ../"Films for you"/rapidapikey.cpp



win32: LIBS += -LC:/Libs/curl-7.77.0-win64-mingw/bin -lcurl
win32: LIBS += -LC:/Libs/curl-7.77.0-win64-mingw/lib -lcurl


INCLUDEPATH += C:/Libs/curl-7.77.0-win64-mingw/include
DEPENDPATH += C:/Libs/curl-7.77.0-win64-mingw/include
