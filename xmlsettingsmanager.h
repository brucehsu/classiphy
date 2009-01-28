#ifndef XMLSETTINGSMANAGER_H
#define XMLSETTINGSMANAGER_H

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>

class XMLSettingsManager
{
    public:
        XMLSettingsManager();

    protected:

    private:
        QFile *docFile;
        QDomDocument *xmlDoc;
};

#endif // XMLSETTINGSMANAGER_H
