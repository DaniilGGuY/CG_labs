QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brezenhem.cpp \
    digitaldifan.cpp \
    draw.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    specfuncs.cpp \
    stepcompare.cpp \
    timescompare.cpp \
    vu.cpp

HEADERS += \
    brezenhem.h \
    digitaldifan.h \
    draw.h \
    mainwindow.h \
    qcustomplot.h \
    specfuncs.h \
    stepcompare.h \
    timescompare.h \
    vu.h

FORMS += \
    mainwindow.ui \
    stepcompare.ui \
    timescompare.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
