#include "xmlsettingsmanager.h"

XMLSettingsManager::XMLSettingsManager() {
    //Initialize objects
    docFile = new QFile("folder_settings.xml");
    xmlDoc = new QDomDocument();

    //Set objects up
    docFile->open(QIODevice::ReadWrite);
    xmlDoc->setContent(docFile);
    QDomElement e = xmlDoc->firstChildElement();
    QDomNode node = e.firstChild();

    //Create document if it's an empty document.
    if(node.isNull()) {
        QDomElement root = xmlDoc->createElement("settings");
        xmlDoc->appendChild(root);
        QDomElement profile = xmlDoc->createElement("profile");
        profile.setAttribute("name","Default");
        root.appendChild(profile);
        for(int i=0;i<9;i++) {
            QDomElement dir = xmlDoc->createElement("dir");
            dir.setAttribute("id",QString::number(i+1));
            profile.appendChild(dir);
            QDomElement path = xmlDoc->createElement("path");
            QDomElement thumb = xmlDoc->createElement("thumb");
            QDomElement rename = xmlDoc->createElement("rename");
            QDomElement digits = xmlDoc->createElement("digits");
            dir.appendChild(path);
            dir.appendChild(thumb);
            dir.appendChild(rename);
            dir.appendChild(digits);
        }
        QString xml = xmlDoc->toString(4);
        QTextStream in(docFile);
        in << xml;
    }
}
