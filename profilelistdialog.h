#ifndef PROFILELISTDIALOG_H
#define PROFILELISTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include "xmlsettingsmanager.h"

class ProfileListDialog : public QDialog
{
    Q_OBJECT
    public:
        ProfileListDialog(QObject *parentw,XMLSettingsManager* manager);

    protected:

    private:
        QGridLayout *layout;
        QListWidget *profileList;
        QPushButton *addBtn,*editBtn,*deleteBtn,*doneBtn;
        QObject *parentWindow;
        XMLSettingsManager *xmlManager;

    public slots:
        void addProfile();
        void editProfile();
        void deleteProfile();
        void refreshProfileList();

        signals:
};

#endif // PROFILELISTDIALOG_H
