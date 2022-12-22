# Tells build system that project uses Qt Core and Qt GUI modules.
QT       += core gui

# Prior to Qt 5 widgets were part of Qt GUI module. In Qt 5 we need to add Qt Widgets module.
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Specifies name of the binary.
TARGET = opengl_switch

# Denotes that project is an application.
TEMPLATE = app

# project files

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# install
target.path = $$[QT_INSTALL_BINS]
INSTALLS += target

RESOURCES += \
    resources.qrc

# windows icon
RC_ICONS = opengl_switch.ico

