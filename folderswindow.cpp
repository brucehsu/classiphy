#include "folderswindow.h"
#include "mainwindow.h"

FoldersWindow::FoldersWindow() {
    //Initialize objects
    layout = new QGridLayout();
    profilesCombo = new QComboBox();
    editProfileBtn = new QPushButton(QObject::trUtf8("Edit Profiles"));
    for(int i=0;i<9;i++) folderBtns.push_back(new FolderButton(i));
    xmlManager = new XMLSettingsManager();
    settingDlg = new FolderSettingDialog(this,xmlManager);
    profileDlg = new ProfileListDialog(this,xmlManager);
    fileManager = new FileManager();

    //Set objects up
    profilesCombo->setEditable(false);
    this->refreshProfiles();
    for(int i=0;i<9;i++) {
        folderBtns[i]->setText(QString::number(i+1));
        folderBtns[i]->setIconSize(QSize(80,80));
        folderBtns[i]->setFixedSize(100,100);
        folderBtns[i]->setStyleSheet(folderBtnDefault);
    }
    getProfileDataByIndex(0);

    //Arrange layout
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(profilesCombo,0,0,1,2);
    layout->addWidget(editProfileBtn,0,2,1,1);
    for(int i=0;i<9;i++) {
        layout->addWidget(folderBtns[i],i/3+1,i%3,1,1);
    }
    layout->setRowStretch(0,1);
    layout->setSpacing(2);

    //Connect slots and signals
    QObject::connect(profilesCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(getProfileDataByIndex(int)));
    QObject::connect(editProfileBtn,SIGNAL(clicked()),profileDlg,SLOT(show()));
    QObject::connect(profileDlg,SIGNAL(accepted()),this,SLOT(refreshProfiles()));
    for(int i=0;i<9;i++) {
        QObject::connect(folderBtns[i],SIGNAL(clicked()),folderBtns[i],SLOT(btnClick()));
        QObject::connect(folderBtns[i],SIGNAL(clicked(int)),settingDlg,SLOT(show(int)));
    }

    this->setLayout(layout);
    this->setWindowFlags(Qt::X11BypassWindowManagerHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFixedSize(315,340);
    this->setWindowTitle(QObject::trUtf8("Folders Window"));
}

void FoldersWindow::getProfileDataByIndex(int index) {
    if(profilesCombo->count()==0) return;
    QString name = profilesCombo->itemText(index);
    xmlManager->setProfile(name);
    paths = xmlManager->getProfileDirPath();
    thumbs = xmlManager->getProfileDirThumb();
    renames = xmlManager->getProfileDirRename();
    digits = xmlManager->getProfileDirDigits();
    refreshFolders();
}

void FoldersWindow::refreshFolders() {
    for(int i=0;i<9;i++) {
        if(paths->at(i)!="") {
            QFileInfo *info = new QFileInfo(paths->at(i));
            if(info->isDir()) {
                QDir *tempDir = new QDir(paths->at(i));
                QString temp = tempDir->dirName();
                folderBtns[i]->setText(temp);
                folderBtns[i]->setStyleSheet(folderBtnPath);
                delete tempDir;
            } else {
                folderBtns[i]->setText(info->fileName());
            }
            delete info;
        } else {
            folderBtns[i]->setText(QString::number(i+1));
            folderBtns[i]->setStyleSheet(folderBtnDefault);
        }
        if(thumbs->at(i)!="") {
            QPixmap pixtemp = QPixmap();
            pixtemp.load(thumbs->at(i));
            pixtemp.scaled(80,80,Qt::KeepAspectRatio,Qt::FastTransformation);
            folderBtns[i]->setIcon(pixtemp);
            folderBtns[i]->setText("");
        } else {
            QPixmap empty = QPixmap();
            folderBtns[i]->setIcon(empty);
        }
    }
}

void FoldersWindow::refreshProfiles() {
    profilesCombo->clear();
    profilesCombo->addItems(xmlManager->getProfiles());
}

void FoldersWindow::moveFile(QString filePath,QString fileName, int destIndex) {
    if(paths->at(destIndex)=="") {
        ((MainWindow*)(parent))->setStatus(QObject::trUtf8("Error: empty destination."));
        return;
    }
    QFileInfo *info = new QFileInfo();
    info->setFile(paths->at(destIndex));
    if(info->isDir()) {
            if(renames->at(destIndex)!="") {
            fileManager->moveFileToFolder(filePath,fileName,paths->at(destIndex),renames->at(destIndex),(digits->at(destIndex)).toInt());
        } else {
            fileManager->moveFileToFolder(filePath,fileName,paths->at(destIndex),fileName);
        }        
        ((MainWindow*)(parent))->setStatus(filePath + "/" + fileName +
                                                 QObject::trUtf8(" has been moved to ") + paths->at(destIndex));
    }
    delete info;
}

void FoldersWindow::copyFile(QString filePath,QString fileName, int destIndex) {
    if(paths->at(destIndex)=="") {
        ((MainWindow*)(parent))->setStatus(QObject::trUtf8("Error: empty destination."));
        return;
    }
    QFileInfo *info = new QFileInfo();
    info->setFile(paths->at(destIndex));
    if(info->isDir()) {
        if(renames->at(destIndex)!="") {
            fileManager->copyFileToFolder(filePath,fileName,paths->at(destIndex),renames->at(destIndex),(digits->at(destIndex)).toInt());
        } else {
            fileManager->copyFileToFolder(filePath,fileName,paths->at(destIndex),fileName);
        }
        ((MainWindow*)(parent))->setStatus(filePath + "/" + fileName +
                                                 QObject::trUtf8(" has been copied to ") + paths->at(destIndex));
    }
    delete info;
}

FileManager* FoldersWindow::getFileManager() {
    return this->fileManager;
}

void FoldersWindow::setVisible(bool visible) {
    this->QWidget::setVisible(visible);
    emit visibility(visible);
}

void FoldersWindow::setParent(QWidget *par) {
    parent = par;
}

void FoldersWindow::setPrevProfile() {
    if(profilesCombo->count()>1) {
        if(profilesCombo->currentIndex()!=0) {
            profilesCombo->setCurrentIndex(profilesCombo->currentIndex()-1);
        } else {
            profilesCombo->setCurrentIndex(profilesCombo->count()-1);
        }
    }
}

void FoldersWindow::setNextProfile() {
    if(profilesCombo->count()>1) {
        if(profilesCombo->currentIndex()==profilesCombo->count()-1) {
            profilesCombo->setCurrentIndex(0);
        } else {
            profilesCombo->setCurrentIndex(profilesCombo->currentIndex()+1);
        }
    }
}
