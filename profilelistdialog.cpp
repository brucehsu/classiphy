#include "profilelistdialog.h"
#include "folderswindow.h"

ProfileListDialog::ProfileListDialog(QObject *parentw,XMLSettingsManager* manager) {
    //Initialize objects.
    profileList = new QListWidget();
    addBtn = new QPushButton(QObject::trUtf8("Add"));
    editBtn = new QPushButton(QObject::trUtf8("Edit"));
    deleteBtn = new QPushButton(QObject::trUtf8("Delete"));
    doneBtn = new QPushButton(QObject::trUtf8("Done"));
    layout = new QGridLayout();

    //Arrange objects
    layout->addWidget(profileList,0,0,1,3);
    layout->addWidget(addBtn,1,0,1,1);
    layout->addWidget(editBtn,1,1,1,1);
    layout->addWidget(deleteBtn,1,2,1,1);
    layout->addWidget(doneBtn,2,0,1,3);

    //Connect slots and signals
    QObject::connect(doneBtn,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(addBtn,SIGNAL(clicked()),this,SLOT(addProfile()));
    QObject::connect(editBtn,SIGNAL(clicked()),this,SLOT(editProfile()));
    QObject::connect(deleteBtn,SIGNAL(clicked()),this,SLOT(deleteProfile()));
    QObject::connect(this,SIGNAL(accepted()),(FoldersWindow*)parentw,SLOT(refreshProfiles()));

    xmlManager = manager;

    refreshProfileList();

    this->setLayout(layout);
    this->setWindowTitle(QObject::trUtf8("Manage Profiles"));
    this->setModal(true);
    this->resize(200,300);
}

void ProfileListDialog::addProfile() {
    bool isOK;
    QString name = QInputDialog::getText(this,QObject::trUtf8("Add Profile"),
                                         QObject::trUtf8("Input the name of the new profile:"),
                                         QLineEdit::Normal, "", &isOK);
    if(isOK) {
        xmlManager->addProfile(name);
    }
    refreshProfileList();
}

void ProfileListDialog::editProfile() {
    bool isOK;
    QString name = QInputDialog::getText(this,QObject::trUtf8("Edit Profile"),
                                         QObject::trUtf8("Input a new name for the profile:"),
                                         QLineEdit::Normal, "", &isOK);
    if(isOK) {
        xmlManager->editProfile(profileList->selectedItems().at(0)->text(),name);
    }
    refreshProfileList();
}

void ProfileListDialog::deleteProfile() {
    QMessageBox message(QMessageBox::NoIcon,QObject::trUtf8("Delete Profile"),
                        QObject::trUtf8("Do you really want to delete this profile?"),
                        QMessageBox::Yes | QMessageBox::No , this);
    if(message.exec() == QMessageBox::Yes) {
        xmlManager->deleteProfile(profileList->selectedItems().at(0)->text());
    }
    refreshProfileList();
}

void ProfileListDialog::refreshProfileList() {
    profileList->clear();
    profileList->addItems(xmlManager->getProfiles());
    profileList->setCurrentRow(0);
    deleteBtn->setEnabled(true);
    if(profileList->count()==1) deleteBtn->setEnabled(false);
}
