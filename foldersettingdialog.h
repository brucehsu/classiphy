#ifndef FOLDERSETTINGDIALOG_H
#define FOLDERSETTINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QFileInfo>
#include <QFileDialog>
#include "xmlsettingsmanager.h"

class FolderSettingDialog : public QDialog
{
    Q_OBJECT

    public:
        FolderSettingDialog(QObject *parentw,XMLSettingsManager* manager);

    protected:

    private:
        QObject *parentWindow;
        QLabel *selectDestLabel,*selectThumbLabel,*renameLabel,*digitsLabel;
        QRadioButton *folderRadioBtn,*zipRadioBtn;
        QPushButton *confirmBtn,*cancelBtn,*selectDestBtn,*selectThumbBtn,*clearThumbBtn;
        QGroupBox *renamingOptions;
        QLineEdit *destEdit,*thumbEdit,*renameEdit;
        QCheckBox *renameCheck;
        QSpinBox *digitsSpin;
        QFileDialog *destDlg, *thumbDlg;
        QHBoxLayout *radioLayout;
        QGridLayout *layout,*renameLayout;
        XMLSettingsManager *xmlManager;
        int currentIndex;

    public slots:
        void show(int);
        void selectDest();
        void selectThumb();
        void setDestFolderMode(bool);
        void setDestZipMode(bool);
        void setDest(QString);
        void setThumb(QString);
        void accept();
};

#endif // FOLDERSETTINGDIALOG_H
