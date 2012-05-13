#-------------------------------------------------
#
# Project created by QtCreator 2011-09-08T15:25:41
#
#-------------------------------------------------

QT       += core gui

TARGET = videozoom
TEMPLATE = app


SOURCES += main.cpp \
    mainpage.cpp \
    process.cpp

HEADERS  += \
    mainpage.h \
    mainpage.h \
    process.h

FORMS    +=

CONFIG += meegotouch
CONFIG += meegotouch-boostable

symbian {
    TARGET.UID3 = 0xe8f85d27
    # TARGET.CAPABILITY +=
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/videozoom/bin
    INSTALLS += target

    icon.path = /usr/share/icons/hicolor/80x80/apps
    icon.files = data/videozoom.png

    desktop.path = /usr/share/applications
    desktop.files = data/videozoom.desktop

    css.path = /opt/videozoom/style/
    css.files = data/videozoom.css

    mod.path = /opt/videozoom/data/
    mod.files = data/camera.conf

    gfx.path = /opt/videozoom/data/
    gfx.files = data/dialog-question.png

    bash.path = /opt/videozoom/bash
    bash.files = data/bash/copyFile data/bash/reboot data/bash/removeFile

    INSTALLS += icon desktop css gfx mod bash

}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

RESOURCES +=
