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
        QHBoxLayout *radioLayout;
        QGridLayout *layout,*renameLayout;
        XMLSettingsManager *xmlManager;
        int currentIndex;

    public slots:
        void show(int);
        void accept();
};

#endif // FOLDERSETTINGDIALOG_H
