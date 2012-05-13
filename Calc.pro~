#-------------------------------------------------
#
# Project created by QtCreator 2011-09-08T15:25:41
#
#-------------------------------------------------

QT       += core gui

TARGET = calc-mtf
TEMPLATE = app


SOURCES += main.cpp \
    mainpage.cpp

HEADERS  += \
    mainpage.h \
    mainpage.h

FORMS    +=

CONFIG += meegotouch

symbian {
    TARGET.UID3 = 0xe8f85d27
    # TARGET.CAPABILITY +=
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/calc-mtf/bin
    INSTALLS += target

    icon.path = /usr/share/icons/hicolor/80x80/apps
    icon.files = data/calc-mtf.png

    desktop.path = /usr/share/applications
    desktop.files = data/calc-mtf.desktop

    css.path = /opt/calc-mtf/style/
    css.files = data/calc-mtf.css

    gfx.path = /opt/calc-mtf/data/
    gfx.files = data/separator340.png

    INSTALLS += icon desktop css gfx

}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

RESOURCES +=
