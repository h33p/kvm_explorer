#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T22:15:04
#
#-------------------------------------------------

QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kvm_explorer
TEMPLATE = app

QMAKE_CXXFLAGS += -ldl -g
QMAKE_LFLAGS += -ldl

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += LMODE=MODE_EXTERNAL MEMUTILS_CUSTOM_RW PATTERN_SCAN_PAGE_SCAN

SOURCES += \
        main.cpp \
    vmread/wintools.c \
    vmread/vmmem.c \
    vmread/mem.c \
    vmread/hlapi/windll.cpp \
    vmread/hlapi/winprocess.cpp \
    vmread/hlapi/winprocesslist.cpp \
    framework/utils/pattern_scan.cpp \
    framework/utils/handles.cpp \
    qhexedit2/src/chunks.cpp \
    qhexedit2/src/commands.cpp \
    qhexedit2/src/qhexedit.cpp \
    mainwindow.cpp \
    qhexedit2/src/QHexEditPlugin.cpp

HEADERS += \
    qhexedit2/src/chunks.h \
    qhexedit2/src/commands.h \
    qhexedit2/src/qhexedit.h \
        mainwindow.h \
    qhexedit2/src/QHexEditPlugin.h

FORMS += \
        mainwindow.ui
