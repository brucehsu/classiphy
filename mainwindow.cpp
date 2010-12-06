#include "mainwindow.h"
#include "const.h"

MainWindow::MainWindow() {
    //Initialize Objects.
    list = new NoSearchList();
    selectFolderBtn = new QPushButton(QObject::trUtf8("Select Folder"));
    foldersWindowBtn = new QPushButton(QObject::trUtf8("Folders Window"));
    foldersWindowBtn->setCheckable(true);
    aboutBtn = new QPushButton(QObject::trUtf8("About"));
    picScroll = new QScrollArea();
    image = new ImageLabel();
    aboutDlg = new AboutDialog();
    foldersWindow = new FoldersWindow();
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
    this->setWindowTitle("classiPHy v" + version + QDir::currentPath());
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
                                                     dir->currentPath()==NULL ? QDir::currentPath() : dir->currentPath(),
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
    } else if(event->key()==Qt::Key_R) { // pressing R//Refresh current directory
        //Refresh current directory
        refreshList();
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
            if(event->modifiers()==Qt::AltModifier) { // pressing Alt+R
                //Rename current selected file
                bool isOk = false;
                QString newName = QInputDialog::getText(this,QObject::trUtf8("Renaming ") + list->item(list->currentRow())->text(),
                                                        QObject::trUtf8("Please input a new file name: ") ,
                                                        QLineEdit::Normal,list->item(list->currentRow())->text(),&isOk);
                if(isOk) {
                    QFile::rename(dir->absolutePath()+"/"+list->item(list->currentRow())->text(),dir->absolutePath()+"/"+newName);
                    refreshList();
                }
            }
            break;

        case Qt::Key_M:
            if(event->modifiers()==Qt::NoModifier) { // pressing M
                //Move current file
                QFileDialog* moveFileDlg = new QFileDialog(this,QObject::trUtf8("Move to..."),this->dir->absolutePath(),QObject::trUtf8("Images") + " (*.jpeg *.tiff *.jpg *.gif *.png)");
                moveFileDlg->setFileMode(QFileDialog::AnyFile);
                moveFileDlg->selectFile(dir->absolutePath()+ "/" +list->item(list->currentRow())->text());
                moveFileDlg->setAcceptMode(QFileDialog::AcceptSave);
                while(true) {
                    if(moveFileDlg->exec()==QDialog::Accepted) {
                        QString path = moveFileDlg->selectedFiles().at(0);
                        if(path!=NULL) {
                            QFileInfo info(path);
                            if(info.exists()) {
                                QMessageBox message(QMessageBox::Warning, QObject::trUtf8("Selected file exists"),
                                                    QObject::trUtf8("Do you want to replace it?"), QMessageBox::Yes | QMessageBox::No , this);
                                if(message.exec()==QMessageBox::No) continue;
                            }
                            foldersWindow->getFileManager()->moveFileToFolder(dir->absolutePath(),list->item(list->currentRow())->text(),info.absoluteDir().absolutePath(),info.fileName());
                        }
                    }
                    break;
                }
                delete moveFileDlg;
                refreshList();
            } else if(event->modifiers()==Qt::AltModifier) { // pressing Alt+M
                //Copy current file
                QFileDialog* copyFileDlg = new QFileDialog(this,QObject::trUtf8("Copy to..."),this->dir->absolutePath(),QObject::trUtf8("Images") + " (*.jpeg *.tiff *.jpg *.gif *.png)");
                copyFileDlg->setFileMode(QFileDialog::AnyFile);
                copyFileDlg->selectFile(dir->absolutePath()+ "/" +list->item(list->currentRow())->text());
                copyFileDlg->setAcceptMode(QFileDialog::AcceptSave);
                while(true) {
                    if(copyFileDlg->exec()==QDialog::Accepted) {
                        QString path = copyFileDlg->selectedFiles().at(0);
                        if(path!=NULL) {
                            QFileInfo info(path);
                            if(info.exists()) {
                                QMessageBox message(QMessageBox::Warning, QObject::trUtf8("Selected file exists"),
                                                    QObject::trUtf8("Do you want to replace it?"), QMessageBox::Yes | QMessageBox::No , this);
                                if(message.exec()==QMessageBox::No) continue;
                            }
                            foldersWindow->getFileManager()->copyFileToFolder(dir->absolutePath(),list->item(list->currentRow())->text(),info.absoluteDir().absolutePath(),info.fileName());
                        }
                    }
                    break;
                }
                delete copyFileDlg;
            }
            break;

        //pressing Alt + num / num only
        //copy file / move file
        case Qt::Key_1 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),0);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),0);
            refreshList();
            break;
        case Qt::Key_2 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),1);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),1);
            refreshList();
            break;
        case Qt::Key_3 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),2);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),2);
            refreshList();
            break;
        case Qt::Key_4 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),3);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),3);
            refreshList();
            break;
        case Qt::Key_5 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),4);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),4);
            refreshList();
            break;
        case Qt::Key_6 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),5);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),5);
            refreshList();
            break;
        case Qt::Key_7 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),6);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),6);
            refreshList();
            break;
        case Qt::Key_8 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),7);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),7);
            refreshList();
            break;
        case Qt::Key_9 :
            if(event->modifiers()==Qt::AltModifier || event->modifiers()==(Qt::AltModifier | Qt::KeypadModifier)) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),8);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),8);
            refreshList();
            break;

        default:
            event->ignore();
    }
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
