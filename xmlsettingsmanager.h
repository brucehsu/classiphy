#ifndef XMLSETTINGSMANAGER_H
#define XMLSETTINGSMANAGER_H

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>

class XMLSettingsManager
{
    public:
        XMLSettingsManager();
        QStringList getProfiles();
        void getProfileDirInfos();
        QStringList* getProfileDirPath();
        QStringList* getProfileDirThumb();
        QStringList* getProfileDirRename();
        QStringList* getProfileDirDigits();
        void setProfile(QString name);
        void addProfile(QString name);
        void deleteProfile(QString name);
        void editProfile(QString originName,QString name);
        void setProfileDirPath(int id,QString text);
        void setProfileDirThumb(int id,QString text);
        void setProfileDirRename(int id,QString text);
        void setProfileDirDigits(int id,QString text);

    protected:
        void writeDocument(QString xml);

    private:
        QString currentProfile;
        QFile *docFile;
        QDomDocument *xmlDoc;
        QStringList *paths,*thumbs,*rename,*digits;
};

#endif // XMLSETTINGSMANAGER_H
