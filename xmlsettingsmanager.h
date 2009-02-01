#ifndef XMLSETTINGSMANAGER_H
#define XMLSETTINGSMANAGER_H

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QStringList>

class XMLSettingsManager
{
    public:
        XMLSettingsManager();
        QStringList getProfiles();
        QStringList* getProfileDirPath();
        QStringList* getProfileDirThumb();
        QStringList* getProfileDirRename();
        QStringList* getProfileDirDigits();
        void setProfile(QString name);
        void addProfile(QString name);
        void deleteProfile(QString name);
        void editProfile(QString originName,QString name);

    protected:

    private:
        QString currentProfile;
        QFile *docFile;
        QDomDocument *xmlDoc;
};

#endif // XMLSETTINGSMANAGER_H
