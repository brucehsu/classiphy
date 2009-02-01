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
        addProfile("Default");
    }
}

QStringList XMLSettingsManager::getProfiles() {
    QStringList *pList = new QStringList();
    QDomNodeList nodes = xmlDoc->elementsByTagName("profile");
    for(int i=0;i<nodes.size();i++) {
        QDomElement temp = nodes.at(i).toElement();
        pList->push_back(temp.attribute("name"));
    }
    return *pList;
}

QStringList* XMLSettingsManager::getProfileDirPath() {
    QStringList *list = new QStringList();
    QDomNodeList nodes = xmlDoc->elementsByTagName("profile");
    QDomElement profile;

    for(int i=0;i<nodes.size();i++) {
        QDomElement temp = nodes.at(i).toElement();
        if(temp.attribute("name")==currentProfile) {
            profile = temp;
            break;
        }
    }

    nodes = profile.elementsByTagName("dir");

    for(int i=0;i<9;i++) {
        for(int j=0;j<nodes.size();j++) {
            QDomElement temp = nodes.at(j).toElement();
            if(temp.attribute("id")==QString::number(i+1)) {
                QDomNodeList tlist = temp.elementsByTagName("path");
                list->push_back(tlist.at(0).toElement().text());
                break;
            }
        }
    }
    return list;
}

QStringList* XMLSettingsManager::getProfileDirThumb() {
    QStringList *list = new QStringList();
    QDomNodeList nodes = xmlDoc->elementsByTagName("profile");
    QDomElement profile;

    for(int i=0;i<nodes.size();i++) {
        QDomElement temp = nodes.at(i).toElement();
        if(temp.attribute("name")==currentProfile) {
            profile = temp;
            break;
        }
    }

    nodes = profile.elementsByTagName("dir");

    for(int i=0;i<9;i++) {
        for(int j=0;j<nodes.size();j++) {
            QDomElement temp = nodes.at(j).toElement();
            if(temp.attribute("id")==QString::number(i+1)) {
                QDomNodeList tlist = temp.elementsByTagName("thumb");
                list->push_back(tlist.at(0).toElement().text());
                break;
            }
        }
    }
    return list;
}

QStringList* XMLSettingsManager::getProfileDirRename() {
    QStringList *list = new QStringList();
    QDomNodeList nodes = xmlDoc->elementsByTagName("profile");
    QDomElement profile;

    for(int i=0;i<nodes.size();i++) {
        QDomElement temp = nodes.at(i).toElement();
        if(temp.attribute("name")==currentProfile) {
            profile = temp;
            break;
        }
    }

    nodes = profile.elementsByTagName("dir");

    for(int i=0;i<9;i++) {
        for(int j=0;j<nodes.size();j++) {
            QDomElement temp = nodes.at(j).toElement();
            if(temp.attribute("id")==QString::number(i+1)) {
                QDomNodeList tlist = temp.elementsByTagName("rename");
                list->push_back(tlist.at(0).toElement().text());
                break;
            }
        }
    }
    return list;
}

QStringList* XMLSettingsManager::getProfileDirDigits() {
    QStringList *list = new QStringList();
    QDomNodeList nodes = xmlDoc->elementsByTagName("profile");
    QDomElement profile;

    for(int i=0;i<nodes.size();i++) {
        QDomElement temp = nodes.at(i).toElement();
        if(temp.attribute("name")==currentProfile) {
            profile = temp;
            break;
        }
    }

    nodes = profile.elementsByTagName("dir");

    for(int i=0;i<9;i++) {
        for(int j=0;j<nodes.size();j++) {
            QDomElement temp = nodes.at(j).toElement();
            if(temp.attribute("id")==QString::number(i+1)) {
                QDomNodeList tlist = temp.elementsByTagName("digits");
                list->push_back(tlist.at(0).toElement().text());
                break;
            }
        }
    }
    return list;
}

void XMLSettingsManager::setProfile(QString name) {
    this->currentProfile = name;
}

void XMLSettingsManager::addProfile(QString name) {
    QDomElement root = xmlDoc->createElement("settings");
    xmlDoc->appendChild(root);
    QDomElement profile = xmlDoc->createElement("profile");
    profile.setAttribute("name",name);
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
