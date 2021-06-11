QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = api
TEMPLATE = app

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    film.cpp \
    filmform.cpp \
    main.cpp \
    mainwindow.cpp \
    profile.cpp \
    profilemenu.cpp

HEADERS += \
    film.h \
    filmform.h \
    mainwindow.h \
    profile.h \
    profilemenu.h

FORMS += \
    filmform.ui \
    mainwindow.ui \
    profilemenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -LC:/Libs/curl-7.77.0-win64-mingw/bin -lcurl
win32: LIBS += -LC:/Libs/curl-7.77.0-win64-mingw/lib -lcurl


INCLUDEPATH += C:/Libs/curl-7.77.0-win64-mingw/include
DEPENDPATH += C:/Libs/curl-7.77.0-win64-mingw/include



