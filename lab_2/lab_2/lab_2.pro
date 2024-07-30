QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edge.cpp \
    edgearr.cpp \
    figure.cpp \
    main.cpp \
    mainwindow.cpp \
    processerror.cpp \
    rotatewindow.cpp \
    scalingwindow.cpp \
    transferwindow.cpp \
    vertex.cpp \
    vertexarr.cpp

HEADERS += \
    edge.h \
    edgearr.h \
    figure.h \
    mainwindow.h \
    processerror.h \
    rotatewindow.h \
    scalingwindow.h \
    transferwindow.h \
    vertex.h \
    vertexarr.h

FORMS += \
    mainwindow.ui \
    rotatewindow.ui \
    scalingwindow.ui \
    transferwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
