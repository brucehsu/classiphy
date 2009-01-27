#include <QMainWindow>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QGridLayout>
#include <QFileDialog>
#include <QDir>
#include "nosearchlist.h"
#include "imagelabel.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
    class MainWindow : QWidget {
        Q_OBJECT

        public:
            MainWindow();
            ~MainWindow();

        private:
            NoSearchList *list;
            QPushButton *selectFolderBtn,*aboutBtn,*foldersWindowBtn;
            QScrollArea *picScroll;
            QGridLayout *layout;
            QFileDialog *selectFolderDlg;
            QDir *dir;
            //PainterWidget image;
            ImageLabel *image;

        public slots:
            void setDir(QString);
            void setImage();

        signals:

    };
#endif // MAINWINDOW_H
