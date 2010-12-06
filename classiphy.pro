# -------------------------------------------------
# Project created by QtCreator 2009-01-26T19:25:06
# -------------------------------------------------
QT += xml
TARGET = classiphy
CONFIG -= app_bundle
CONFIG += moc
CONFIG += static
QTPLUGIN += qjpeg \
    qgif \
    qtiff
TEMPLATE = app
TRANSLATIONS += classiPHy_lang.ts
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
    filemanager.cpp
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
    filemanager.h
OTHER_FILES += classiPHy_lang.ts
