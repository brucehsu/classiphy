#ifndef FOLDERSWINDOW_H
#define FOLDERSWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDir>
#include <QLabel>
#include "xmlsettingsmanager.h"
#include "folderbutton.h"
#include "foldersettingdialog.h"
#include "profilelistdialog.h"
#include "filemanager.h"

const QString folderBtnDefault("QPushButton{"
                                 "font: bold 48px;}");
const QString folderBtnPath("QPushButton{}");


class FoldersWindow : public QWidget
{
    Q_OBJECT

    public:
        FoldersWindow();
        void refreshFolders();
        void moveFile(QString filePath,QString fileName,int destIndex);
        void copyFile(QString filePath,QString fileName,int destIndex);
        void setParent(QWidget *par);
        void setPrevProfile();
        void setNextProfile();
        void toggleLayout();
        FileManager* getFileManager();

    protected:

    private:
        void changeLayout();
        QGridLayout *layout;
        QComboBox *profilesCombo;
        QPushButton *editProfileBtn;
        QVector<FolderButton*> folderBtns;
        XMLSettingsManager *xmlManager;
        QStringList *paths,*thumbs,*renames,*digits;
        FolderSettingDialog *settingDlg;
        ProfileListDialog *profileDlg;
        FileManager *fileManager;
        QWidget* parent;
        QLabel *btnLayoutLabel;
        bool isNumpad;

    public slots:
        void getProfileDataByIndex(int);
        void refreshProfiles();
        void setVisible(bool visible);

        signals:
            void visibility(bool);
};

#endif // FOLDERSWINDOW_H
