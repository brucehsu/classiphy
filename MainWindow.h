#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QGridLayout>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include "nosearchlist.h"
#include "imagelabel.h"
#include "aboutdialog.h"
#include "folderswindow.h"

    class MainWindow : QWidget {
        Q_OBJECT

        public:
            MainWindow();
            //~MainWindow();

        protected:
            void resizeEvent(QResizeEvent*);
            void keyPressEvent(QKeyEvent*);
            void keyReleaseEvent(QKeyEvent*);
            void closeEvent(QCloseEvent*);

        private:
            NoSearchList *list;
            QPushButton *selectFolderBtn,*aboutBtn,*foldersWindowBtn;
            QScrollArea *picScroll;
            QGridLayout *layout;
            QFileDialog *selectFolderDlg;
            QDir *dir;
            ImageLabel *image;
            AboutDialog *aboutDlg;
            FoldersWindow *foldersWindow;

        public slots:
            void setDir(QString);
            void setImage();

        signals:

    };
#endif // MAINWINDOW_H