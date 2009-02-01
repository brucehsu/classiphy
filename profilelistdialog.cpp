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

    profileList->addItems(manager->getProfiles());

    //Arrange objects
    layout->addWidget(profileList,0,0,1,3);
    layout->addWidget(addBtn,1,0,1,1);
    layout->addWidget(editBtn,1,1,1,1);
    layout->addWidget(deleteBtn,1,2,1,1);
    layout->addWidget(doneBtn,2,0,1,3);

    //Connect slots and signals
    QObject::connect(doneBtn,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(this,SIGNAL(accepted()),(FoldersWindow*)parentw,SLOT(refreshProfiles()));

    xmlManager = manager;
    this->setLayout(layout);
    this->setWindowTitle(QObject::trUtf8("Manage Profiles"));
    this->setModal(true);
    this->resize(200,300);
}
