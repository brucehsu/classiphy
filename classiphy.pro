# -------------------------------------------------
# Project created by QtCreator 2009-01-26T19:25:06
# -------------------------------------------------
QT += xml widgets
TARGET = classiphy
CONFIG -= app_bundle
CONFIG += moc

win32 {
	CONFIG += static
	DEFINES += STATIC
	QTPLUGIN += qjpeg \
	    qgif \
	    qtiff
}

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    BINDIR = $$PREFIX/bin

    INSTALLS += target
    target.path = $$BINDIR
}

TEMPLATE = app
TRANSLATIONS += classiphy_zh_TW.ts
SOURCES += main.cpp \
    mainwindow.cpp \
    nosearchlist.cpp \
    imagelabel.cpp \
    aboutdialog.cpp \
    xmlsettingsmanager.cpp \
    folderswindow.cpp \
    folderbutton.cpp \
    foldersettingdialog.cpp \
    profilelistdialog.cpp \
    filemanager.cpp \
    nosearchcombobox.cpp
HEADERS += mainwindow.h \
    const.h \
    nosearchlist.h \
    imagelabel.h \
    aboutdialog.h \
    xmlsettingsmanager.h \
    folderswindow.h \
    folderbutton.h \
    foldersettingdialog.h \
    profilelistdialog.h \
    filemanager.h \
    nosearchcombobox.h
OTHER_FILES += classiphy_zh_TW.ts

RESOURCES += \
    resource.qrc


