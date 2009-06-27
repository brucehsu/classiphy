# -------------------------------------------------
# Project created by QtCreator 2009-01-26T19:25:06
# -------------------------------------------------
QT += xml
TARGET = classiPHy
CONFIG -= app_bundle
CONFIG += moc
CONFIG += static
#LIBS += -L third_party/zlib \
#    -lz
INCLUDEPATH += third_party/zlib
QTPLUGIN += qjpeg \
    qgif \
    qtiff
TEMPLATE = app
TRANSLATIONS += classiPHy_lang.ts
SOURCES += main.cpp \
    MainWindow.cpp \
    nosearchlist.cpp \
    imagelabel.cpp \
    aboutdialog.cpp \
    xmlsettingsmanager.cpp \
    folderswindow.cpp \
    folderbutton.cpp \
    foldersettingdialog.cpp \
    profilelistdialog.cpp \
    filemanager.cpp \
    third_party/quazip/quazip/zip.c \
    third_party/quazip/quazip/unzip.c \
    third_party/quazip/quazip/quazipnewinfo.cpp \
    third_party/quazip/quazip/quazipfile.cpp \
    third_party/quazip/quazip/quazip.cpp \
    third_party/quazip/quazip/ioapi.c
HEADERS += MainWindow.h \
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
    third_party/quazip/quazip/zip.h \
    third_party/quazip/quazip/unzip.h \
    third_party/quazip/quazip/quazipnewinfo.h \
    third_party/quazip/quazip/quazipfileinfo.h \
    third_party/quazip/quazip/quazipfile.h \
    third_party/quazip/quazip/quazip.h \
    third_party/quazip/quazip/ioapi.h \
    third_party/quazip/quazip/crypt.h
OTHER_FILES += classiPHy_lang.ts
