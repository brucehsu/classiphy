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
    int count = list->count();

    //Pre-select the first item to avoid runtime error encounted when clearing the list.
    list->setCurrentRow(0);
    image->clearImage();

    //Clear the list.
    for(int i=0;i<count;i++) list->takeItem(0);
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
    switch(event->key()) {
        case Qt::Key_T :
            //Switch thumbnail mode on/off.
            image->thumbSwitch();
            image->refresh();
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
    delete foldersWindow;
    delete aboutDlg;
    QApplication::quit();
}
