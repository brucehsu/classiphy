#include "MainWindow.h"
#include "const.h"

MainWindow::MainWindow() {
    //Initialize Objects.
    list = new NoSearchList();
    selectFolderBtn = new QPushButton(QObject::trUtf8("Select Folder"));
    foldersWindowBtn = new QPushButton(QObject::trUtf8("Folders Window"));
    aboutBtn = new QPushButton(QObject::trUtf8("About"));
    picScroll = new QScrollArea();
    image = new ImageLabel();
    selectFolderDlg = new QFileDialog(this,QObject::trUtf8("Select a folder"));
    aboutDlg = new AboutDialog();
    foldersWindow = new FoldersWindow();
    layout = new QGridLayout();
    dir = new QDir();

    //Arrange layout.
    layout->addWidget(picScroll,0,0,9,11);
    layout->addWidget(list,0,12,6,2);
    layout->addWidget(foldersWindowBtn,6,12,1,2);
    layout->addWidget(selectFolderBtn,7,12,1,2);
    layout->addWidget(aboutBtn,8,12,1,2);

    //Set selectFolderDlg.
    selectFolderDlg->setFileMode(QFileDialog::DirectoryOnly);
    selectFolderDlg->setViewMode(QFileDialog::List);

    //Set list.
    list->setSelectionMode(QListWidget::SingleSelection);

    //Connect slots and signals.
    QObject::connect(selectFolderBtn,SIGNAL(clicked()),selectFolderDlg,SLOT(open()));
    QObject::connect(selectFolderDlg,SIGNAL(fileSelected(QString)),this,SLOT(setDir(QString)));
    QObject::connect(aboutBtn,SIGNAL(clicked()),aboutDlg,SLOT(exec()));
    QObject::connect(list,SIGNAL(itemSelectionChanged()),this,SLOT(setImage()));
    QObject::connect(foldersWindowBtn,SIGNAL(clicked()),foldersWindow,SLOT(show()));

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
}

void MainWindow::setImage() {
    QString path = dir->absolutePath() + "/" + list->currentItem()->text();
    image->setImage(path);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    image->refresh();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Control) {
        foldersWindow->setVisible(true);
        this->activateWindow();
        this->raise();
    }
    if(event->key()==Qt::Key_Z) {
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
                    QFile *deletedFile = new QFile(dir->absolutePath() + "/" + list->currentItem()->text());
                    deletedFile->remove();
                    refreshList();
                    delete deletedFile;
                }
            }
            break;
        case Qt::Key_R:
            if(event->modifiers()==Qt::ControlModifier) {
                refreshList();
            } else if(event->modifiers()==Qt::AltModifier) {

            }
            break;
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
        default:
            event->ignore();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Control) {
        foldersWindow->setVisible(false);
        this->activateWindow();
        this->raise();
    }
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
