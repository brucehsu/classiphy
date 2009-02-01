#ifndef FOLDERSWINDOW_H
#define FOLDERSWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDir>
#include "xmlsettingsmanager.h"
#include "folderbutton.h"
#include "foldersettingdialog.h"
#include "profilelistdialog.h"

class FoldersWindow : public QWidget
{
    Q_OBJECT

    public:
        FoldersWindow();
        void refreshFolders();

    protected:

    private:
        QGridLayout *layout;
        QComboBox *profilesCombo;
        QPushButton *editProfileBtn;
        QVector<FolderButton*> folderBtns;
        XMLSettingsManager *xmlManager;
        QStringList *paths,*thumbs,*renames,*digits;
        FolderSettingDialog *settingDlg;
        ProfileListDialog *profileDlg;

    public slots:
        void getProfileDataByIndex(int);
        void refreshProfiles();
        void getButton(int);

        signals:
};

#endif // FOLDERSWINDOW_H
