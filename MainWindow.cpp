#include "MainWindow.h"
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
    selectFolderDlg = new QFileDialog(this,QObject::trUtf8("Select a folder"));
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

    //Set selectFolderDlg.
    selectFolderDlg->setFileMode(QFileDialog::DirectoryOnly);
    selectFolderDlg->setViewMode(QFileDialog::List);

    //Set list.
    list->setSelectionMode(QListWidget::SingleSelection);

    //Set status
    status->setFixedHeight(30);
    status->setStyleSheet("QStatusBar {border: 2px solid grey;border-radius: 3px;}");
    status->showMessage(QObject::trUtf8("Ready"));

    //set foldersWindow
    foldersWindow->setParent(this);

    //Connect slots and signals.
    QObject::connect(selectFolderBtn,SIGNAL(clicked()),selectFolderDlg,SLOT(open()));
    QObject::connect(selectFolderDlg,SIGNAL(fileSelected(QString)),this,SLOT(setDir(QString)));
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

void MainWindow::setDir(QString dirname) {
    dir->setPath(dirname);
    QStringList filter;
    filter << "*.jpeg" << "*.jpg" << "*.gif" << "*.png" << "*.tiff";
    QStringList items = dir->entryList(filter,QDir::Files);

    //Pre-select the first item to avoid runtime error when clearing the list.
    list->setCurrentRow(0);
    image->clearImage();

    //Clear the list.
    list->clear();
    list->addItems(items);
    list->setCurrentRow(0);
    selectFolderDlg->setDirectory(*dir);
}

void MainWindow::setImage() {
    QString path = dir->absolutePath() + "/" + list->currentItem()->text();
    image->setImage(path);
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
        this->refreshList();
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
                    "Are you sure?", QMessageBox::Yes | QMessageBox::No);
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
                QString newName = QInputDialog::getText(this,QObject::trUtf8("Renaming ") + list->item(list->currentRow())->text(),
                                                        QObject::trUtf8("Please input a new file name: ") ,
                                                        QLineEdit::Normal,list->item(list->currentRow())->text(),&isOk);
                if(isOk) {
                    QFile::rename(dir->absolutePath()+"/"+list->item(list->currentRow())->text(),dir->absolutePath()+"/"+newName);
                    refreshList();
                }
            }
            break;

        //pressing Alt + num / num only
        //copy file / move file
        case Qt::Key_1 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),0);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),0);
            refreshList();
            break;
        case Qt::Key_2 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),1);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),1);
            refreshList();
            break;
        case Qt::Key_3 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),2);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),2);
            refreshList();
            break;
        case Qt::Key_4 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),3);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),3);
            refreshList();
            break;
        case Qt::Key_5 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),4);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),4);
            refreshList();
            break;
        case Qt::Key_6 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),5);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),5);
            refreshList();
            break;
        case Qt::Key_7 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),6);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),6);
            refreshList();
            break;
        case Qt::Key_8 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),7);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),7);
            refreshList();
            break;
        case Qt::Key_9 :
            if(event->modifiers()==Qt::AltModifier) foldersWindow->copyFile(dir->absolutePath(),list->item(list->currentRow())->text(),8);
            else foldersWindow->moveFile(dir->absolutePath(),list->item(list->currentRow())->text(),8);
            refreshList();
            break;

        //Change current profile
        //pressing left for previous, right for next
        case Qt::Key_Left :
            foldersWindow->setPrevProfile();
            break;
        case Qt::Key_Right :
            foldersWindow->setNextProfile();
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
    int currentIndex = list->currentRow();
    setDir(dir->absolutePath());
    if(currentIndex>=list->count()) {
        list->setCurrentRow(list->count()-1);
    } else list->setCurrentRow(currentIndex);
}

void MainWindow::setStatus(QString stat) {
    status->showMessage(stat);
}
