#ifndef FOLDERSETTINGDIALOG_H
#define FOLDERSETTINGDIALOG_H

#include <QDialog>
#include "xmlsettingsmanager.h"

class FolderSettingDialog : public QDialog
{
    public:
        FolderSettingDialog(XMLSettingsManager* manager);

    protected:

    private:
        XMLSettingsManager *xmlManager;
};

#endif // FOLDERSETTINGDIALOG_H
