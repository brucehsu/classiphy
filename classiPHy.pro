# -------------------------------------------------
# Project created by QtCreator 2009-01-26T19:25:06
# -------------------------------------------------
QT += xml
TARGET = classiPHy
CONFIG -= app_bundle
CONFIG += moc
CONFIG += static
INCLUDEPATH += C:\Qt\4.5.0-beta1\src\3rdparty
QMAKE_CXXFLAGS += -pipe \
    -O2
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
    third_party/OSDaB-Zip/zip.cpp \
    third_party/OSDaB-Zip/unzip.cpp
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
    third_party/OSDaB-Zip/zip_p.h \
    third_party/OSDaB-Zip/zip.h \
    third_party/OSDaB-Zip/unzip_p.h \
    third_party/OSDaB-Zip/unzip.h \
    third_party/OSDaB-Zip/zipentry_p.h
OTHER_FILES += classiPHy_lang.ts
