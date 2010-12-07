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
#include <QMessageBox>
#include <QStatusBar>
#include "nosearchlist.h"
#include "imagelabel.h"
#include "aboutdialog.h"
#include "folderswindow.h"

    class MainWindow : QWidget {
        Q_OBJECT

        public:
            MainWindow();
            void refreshList();
            void setStatus(QString stat);
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
            QStatusBar *status;
            ImageLabel *image;
            AboutDialog *aboutDlg;
            FoldersWindow *foldersWindow;

        public slots:
            void selectDir();
            void setDir(QString);
            void setImage();
            void processKeyEvent(QKeyEvent*);

        signals:

    };
#endif // MAINWINDOW_H
