#include "mainwindow.h"
#include "const.h"

MainWindow::MainWindow() {
    //Initialize Objects.
    list = new NoSearchList(this);
    selectFolderBtn = new QPushButton(QObject::trUtf8("Select Folder"));
    foldersWindowBtn = new QPushButton(QObject::trUtf8("Folders Window"));
    foldersWindowBtn->setCheckable(true);
    aboutBtn = new QPushButton(QObject::trUtf8("About"));
    picScroll = new QScrollArea();
    image = new ImageLabel();
    aboutDlg = new AboutDialog();
    foldersWindow = new FoldersWindow(this);
    layout = new QGridLayout();
    dir = new QDir();
    status = new QStatusBar(this);

    //Arrange layout.
    layout->addWidget(picScroll,0,0,9,12);
    layout->addWidget(list,0,12,6,2);
    layout->addWidget(foldersWindowBtn,6,12,1,2);
    layout->addWidget(selectFolderBtn,7,12,1,2);
    layout->addWidget(aboutBtn,8,12,1,2);
    layout->addWidget(status,9,0,1,14);

    //Set list.
    list->setSelectionMode(QListWidget::SingleSelection);

    //Set status
    status->setFixedHeight(30);
    status->setStyleSheet("QStatusBar {border: 2px solid grey;border-radius: 3px;}");
    status->showMessage(QObject::trUtf8("Ready"));

    //set foldersWindow
    foldersWindow->setParent(this);

    //Connect slots and signals.
    QObject::connect(selectFolderBtn,SIGNAL(clicked()),this,SLOT(selectDir()));
    QObject::connect(aboutBtn,SIGNAL(clicked()),aboutDlg,SLOT(exec()));
    QObject::connect(list,SIGNAL(itemSelectionChanged()),this,SLOT(setImage()));
    QObject::connect(foldersWindowBtn,SIGNAL(toggled(bool)),foldersWindow,SLOT(setVisible(bool)));
    QObject::connect(foldersWindow,SIGNAL(visibility(bool)),foldersWindowBtn,SLOT(setChecked(bool)));

    this->setLayout(layout);
    this->setWindowTitle("classiPHy v" + version);
    this->resize(720,500);
    this->show();

    picScroll->show();
    picScroll->setAlignment(Qt::AlignCenter);
    picScroll->setWidget(image);
    image->setParent(picScroll);
    image->show();
}

void MainWindow::selectDir() {
    QString path = QFileDialog::getExistingDirectory(this, QObject::trUtf8("Select a folder"),
                                                     dir->absolutePath()==NULL ? QDir::currentPath() : dir->absolutePath(),
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(path!=NULL) {
        this->setDir(path);
    }
}

void MainWindow::setDir(QString dirname) {
    dir->setPath(dirname);
    QStringList filter;
    filter << "*.jpeg" << "*.jpg" << "*.gif" << "*.png" << "*.tiff";
    QStringList items = dir->entryList(filter,QDir::Files);

    //Pre-select the first item to avoid runtime error when clearing the list.
    list->setCurrentRow(0);

    //Clear the list.
    list->clear();
    image->clearImage();
    list->addItems(items);
    list->setCurrentRow(0);
    this->setWindowTitle("classiPHy v" + version + " - " + dir->absolutePath());
}

void MainWindow::setImage() {
    if(list->count()==0) {
        image->clearImage();
    } else {
        QString path = dir->absolutePath() + "/" + list->currentItem()->text();
        image->setImage(path);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    image->refresh();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    this->processKeyEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    /*if(event->key()==Qt::Key_Control) {
        foldersWindow->setVisible(false);
        this->activateWindow();
        this->raise();
    }*/
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QApplication::quit();
}

void MainWindow::refreshList() {
    int currentIndex = 0;
    if(list->count()!=0) currentIndex = list->currentRow();
    setDir(dir->absolutePath());
    if(currentIndex>=list->count()) {
        list->setCurrentRow(list->count()-1);
    } else list->setCurrentRow(currentIndex);
}

void MainWindow::setStatus(QString stat) {
    status->showMessage(stat);
}

void MainWindow::processKeyEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Control) { // pressing ctrl
        //Toggle folders window
        if(foldersWindow->isVisible()) {
            foldersWindow->setVisible(false);
        } else {
            foldersWindow->setVisible(true);
        }
        this->activateWindow();
        this->raise();
    }

    if(event->key()==Qt::Key_Z) { //pressing Z
        //Undo change
        foldersWindow->getFileManager()->undoChange();
        refreshList();
        return;
    } else if(event->key()==Qt::Key_Left) { // pressing left
        //Switch current profile to previous profile
        foldersWindow->setPrevProfile();
        return;
    } else if(event->key()==Qt::Key_Right) { // pressing right
        //Switch current profile to next profile
        foldersWindow->setNextProfile();
        return;
    }

    if(event->key()==Qt::Key_L) { //pressing L
        //Toggle folder button layout
        foldersWindow->toggleLayout();
        return;
    }

    if(list->count()==0) return;

    switch(event->key()) {

        case Qt::Key_T :
            //Switch thumbnail mode on/off.
            image->thumbSwitch();
            image->refresh();
            break;

        case Qt::Key_Delete : {
                //Delete current selected file.
                int deletion = QMessageBox::warning(this,QObject::trUtf8("Deleting File: ") + list->currentItem()->text(),
                    "Once the file is deleted, the operation cannot be undone.\nAre you sure? ", QMessageBox::Yes | QMessageBox::No);
                if(deletion==QMessageBox::Yes) {
                    QFile::remove(dir->absolutePath() + "/" + list->currentItem()->text());
                    refreshList();
                }
            }
            break;

        case Qt::Key_R:
            if(event->modifiers()==Qt::NoModifier) { // pressing R
                //Refresh current directory
                refreshList();
            } else if(event->modifiers()==Qt::AltModifier) { // pressing Alt+R
                //Rename current selected file
                bool isOk = false;
                QString newName = QInputDialog::getText(this,QObject::trUtf8("Renaming ") + list->currentItem()->text(),
                                                        QObject::trUtf8("Please input a new file name: ") ,
                                                        QLineEdit::Normal,list->currentItem()->text(),&isOk);
                if(isOk) {
                    QFile::rename(dir->absolutePath()+"/" + list->currentItem()->text(),dir->absolutePath()+"/"+newName);
                    refreshList();
                }
            }
            break;

        case Qt::Key_M:
            if(event->modifiers()==Qt::NoModifier) { // pressing M
                //Move current file
                QString fileName = QFileDialog::getSaveFileName(this, QObject::trUtf8("Move to...") ,
                                           dir->absolutePath() + "/" + list->currentItem()->text(),
                                           QObject::trUtf8("Images") + " (*.jpeg *.tiff *.jpg *.gif *.png)");
                if(fileName!=0) {
                    foldersWindow->getFileManager()->moveFileToFolder(dir->absolutePath(),list->currentItem()->text(),fileName.left(fileName.lastIndexOf("/")),fileName.right(fileName.length() - fileName.lastIndexOf("/")));
                    refreshList();
                }
            } else if(event->modifiers()==Qt::AltModifier) { // pressing Alt+M
                //Copy current file
                QString fileName = QFileDialog::getSaveFileName(this, QObject::trUtf8("Copy to...") ,
                                           dir->absolutePath() + "/" + list->currentItem()->text(),
                                           QObject::trUtf8("Images") + " (*.jpeg *.tiff *.jpg *.gif *.png)");
                if(fileName!=0) {
                    foldersWindow->getFileManager()->copyFileToFolder(dir->absolutePath(),list->currentItem()->text(),fileName.left(fileName.lastIndexOf("/")),fileName.right(fileName.length() - fileName.lastIndexOf("/")));
                    refreshList();
                }
            }
            break;

        //pressing Alt + num / num only
        //copy file / move file
        case Qt::Key_1 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),0);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),0);
            refreshList();
            break;
        case Qt::Key_2 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),1);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),1);
            refreshList();
            break;
        case Qt::Key_3 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),2);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),2);
            refreshList();
            break;
        case Qt::Key_4 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),3);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),3);
            refreshList();
            break;
        case Qt::Key_5 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),4);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),4);
            refreshList();
            break;
        case Qt::Key_6 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),5);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),5);
            refreshList();
            break;
        case Qt::Key_7 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),6);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),6);
            refreshList();
            break;
        case Qt::Key_8 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),7);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),7);
            refreshList();
            break;
        case Qt::Key_9 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->currentItem()->text(),8);
            else foldersWindow->moveFile(dir->absolutePath(),list->currentItem()->text(),8);
            refreshList();
            break;

        default:
            event->ignore();
    }
}
