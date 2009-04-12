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
#include "filemanager.h"

class FoldersWindow : public QWidget
{
    Q_OBJECT

    public:
        FoldersWindow();
        void refreshFolders();
        void moveFile(QString filePath,QString fileName,int destIndex);
        void copyFile(QString filePath,QString fileName,int destIndex);

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
        FileManager *fileManager;

    public slots:
        void getProfileDataByIndex(int);
        void refreshProfiles();

        signals:
};

#endif // FOLDERSWINDOW_H
