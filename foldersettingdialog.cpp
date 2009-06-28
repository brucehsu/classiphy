#include "foldersettingdialog.h"
#include "folderswindow.h"

FolderSettingDialog::FolderSettingDialog(QObject *parentw, XMLSettingsManager* manager) {
    //Initialize objects
    parentWindow = parentw;
    selectDestLabel = new QLabel(QObject::trUtf8("Select Destination"));
    selectThumbLabel = new QLabel(QObject::trUtf8("Select Thumbnail"));
    renameLabel = new QLabel(QObject::trUtf8("File name"));
    digitsLabel = new QLabel(QObject::trUtf8("Digits"));
    selectDestBtn = new QPushButton("...");
    selectThumbBtn = new QPushButton("...");
    clearThumbBtn = new QPushButton(QObject::trUtf8("Clear"));
    confirmBtn = new QPushButton(QObject::trUtf8("Confirm"));
    cancelBtn = new QPushButton(QObject::trUtf8("Cancel"));
    folderRadioBtn = new QRadioButton(QObject::trUtf8("Folder"));
    zipRadioBtn = new QRadioButton(QObject::trUtf8("Zip file"));
    renameCheck = new QCheckBox(QObject::trUtf8("Enable"));
    renamingOptions = new QGroupBox(QObject::trUtf8("Renaming Rules"));
    destEdit = new QLineEdit();
    thumbEdit = new QLineEdit();
    renameEdit = new QLineEdit();
    digitsSpin = new QSpinBox();
    radioLayout = new QHBoxLayout();
    layout = new QGridLayout();
    renameLayout = new QGridLayout();
    destDlg = new QFileDialog(this,QObject::trUtf8("Select Destination"));
    thumbDlg = new QFileDialog(this,QObject::trUtf8("Select Thumbnail"));

    //Arrange layout
    selectDestBtn->setMaximumWidth(60);
    selectThumbBtn->setMaximumWidth(60);
    clearThumbBtn->setMaximumWidth(60);
    radioLayout->setAlignment(Qt::AlignHCenter);
    radioLayout->addWidget(folderRadioBtn);
    radioLayout->addWidget(zipRadioBtn);
    layout->addLayout(radioLayout,0,0,1,12);
    layout->addWidget(selectDestLabel,1,0,1,12);
    layout->addWidget(destEdit,2,0,1,11);
    layout->addWidget(selectDestBtn,2,11,1,1);
    layout->addWidget(selectThumbLabel,3,0,1,12);
    layout->addWidget(thumbEdit,4,0,1,10);
    layout->addWidget(selectThumbBtn,4,10,1,1);
    layout->addWidget(clearThumbBtn,4,11,1,1);
    renameLayout->addWidget(renameCheck,0,0,1,4);
    renameLayout->addWidget(renameLabel,1,0,1,1);
    renameLayout->addWidget(renameEdit,1,1,1,2);
    renameLayout->addWidget(digitsLabel,2,0,1,1);
    renameLayout->addWidget(digitsSpin,2,1,1,2);
    renamingOptions->setLayout(renameLayout);
    layout->addWidget(renamingOptions,5,0,3,12);
    layout->addWidget(confirmBtn,8,0,1,6);
    layout->addWidget(cancelBtn,8,6,1,6);
    this->setLayout(layout);

    //Set objects up
    destEdit->setReadOnly(true);
    thumbEdit->setReadOnly(true);
    thumbDlg->setFilter(QObject::trUtf8("Images") + " (*.jpeg *.tiff *.jpg *.gif *.png)");

    //Connect slots and signals
    QObject::connect(folderRadioBtn,SIGNAL(toggled(bool)),this,SLOT(setDestFolderMode(bool)));
    QObject::connect(zipRadioBtn,SIGNAL(toggled(bool)),this,SLOT(setDestZipMode(bool)));
    QObject::connect(selectDestBtn,SIGNAL(clicked()),destDlg,SLOT(show()));
    QObject::connect(selectThumbBtn,SIGNAL(clicked()),thumbDlg,SLOT(show()));
    QObject::connect(clearThumbBtn,SIGNAL(clicked()),thumbEdit,SLOT(clear()));
    QObject::connect(destDlg,SIGNAL(fileSelected(QString)),this,SLOT(setDest(QString)));
    QObject::connect(thumbDlg,SIGNAL(fileSelected(QString)),this,SLOT(setThumb(QString)));
    QObject::connect(confirmBtn,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(renameCheck,SIGNAL(toggled(bool)),digitsSpin,SLOT(setEnabled(bool)));
    QObject::connect(renameCheck,SIGNAL(toggled(bool)),renameEdit,SLOT(setEnabled(bool)));

    xmlManager = manager;
    this->setModal(true);
    this->setWindowFlags(Qt::X11BypassWindowManagerHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowTitle(QObject::trUtf8("Folder Setting"));
    this->setFixedSize(300,350);
}

void FolderSettingDialog::show(int num) {
    QString path = xmlManager->getProfileDirPath()->at(num);
    QFileInfo *info = new QFileInfo(path);
    destEdit->setText(path);
    destDlg->setDirectory(info->isDir()? path : info->absoluteDir());
    thumbDlg->setDirectory(info->isDir()? path : info->absoluteDir());

    if(xmlManager->getProfileDirThumb()->at(num)!="") {
        QFileInfo *thumbInfo = new QFileInfo(xmlManager->getProfileDirThumb()->at(num));
        thumbEdit->setText(thumbInfo->absoluteFilePath());
        thumbDlg->setDirectory(thumbInfo->absoluteDir());
        delete thumbInfo;
    }

    if(info->isDir()) {
        folderRadioBtn->setChecked(true);
    } else {
        zipRadioBtn->setChecked(true);
    }
    if(path=="") {
        folderRadioBtn->setChecked(true);
    }

    if(xmlManager->getProfileDirRename()->at(num)!="") {
        renameCheck->setChecked(false);
        renameCheck->toggle();
        renameEdit->setText(xmlManager->getProfileDirRename()->at(num));
        QString digits = xmlManager->getProfileDirDigits()->at(num);
        digitsSpin->setValue(digits.toInt());
    } else {
        renameCheck->setChecked(true);
        renameCheck->toggle();
        renameEdit->setText("");
        digitsSpin->setValue(0);
    }

    currentIndex = num;
    delete info;
    ((QDialog*)this)->show();
}

void FolderSettingDialog::accept() {
    xmlManager->setProfileDirPath(currentIndex,destEdit->text());
    xmlManager->setProfileDirThumb(currentIndex,thumbEdit->text());

    if(renameCheck->isChecked()) {
        xmlManager->setProfileDirRename(currentIndex,renameEdit->text());
        xmlManager->setProfileDirDigits(currentIndex,QString::number(digitsSpin->value()));
    } else {
        xmlManager->setProfileDirRename(currentIndex,"");
        xmlManager->setProfileDirDigits(currentIndex,"");
    }

    xmlManager->getProfileDirInfos();
    ((FoldersWindow*) parentWindow)->refreshFolders();
    this->close();
}

void FolderSettingDialog::setDestFolderMode(bool isFolder) {
    if(isFolder) {
        destDlg->setOption(QFileDialog::ShowDirsOnly,true);
        destDlg->setFileMode(QFileDialog::DirectoryOnly);
        destDlg->setViewMode(QFileDialog::List);
    }
}

void FolderSettingDialog::setDestZipMode(bool isZip) {
    if(isZip) {
        destDlg->setFileMode(QFileDialog::AnyFile);
        destDlg->setFilter("*.zip");
    }
}

void FolderSettingDialog::setDest(QString fileName) {
    destEdit->setText(fileName);
}

void FolderSettingDialog::setThumb(QString fileName) {
    thumbEdit->setText(fileName);
}
