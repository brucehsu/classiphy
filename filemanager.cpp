#include "filemanager.h"

FileManager::FileManager()
{
}

void FileManager::deleteFile(QString path) {
    QFile *originFile = new QFile(path);
    if(!originFile->exists()) return;
    originFile->remove();
    delete originFile;
}

void FileManager::copyFileToFolder(QString originPath, QString originName,QString newPath,QString newName) {
    QFile *originFile = new QFile(originPath + "/" + originName);
    if(QString::compare(originPath,newPath)==0 && QString::compare(originName,newName)==0) return;
    if(QFile::exists(newPath+"/"+newName)) QFile::remove(newPath+"/"+newName);
    originFile->copy(newPath + "/" + newName);
    delete originFile;
}

void FileManager::copyFileToFolder(QString originPath, QString originName,QString newPath,QString rename,int digits) {
    QFileInfo* info = new QFileInfo(originPath + "/" + originName);
    QString name = generateName(newPath,rename,info->completeSuffix(),digits);
    copyFileToFolder(originPath,originName, newPath, name);
    historyFromPath.push(originPath);
    historyFromName.push(originName);
    historyToPath.push(newPath);
    historyToName.push(name);
    historyType.push_back("folder");
    delete info;
}

void FileManager::moveFileToFolder(QString originPath, QString originName,QString newPath,QString newName) {
    if(QString::compare(originPath,newPath)==0 && QString::compare(originName,newName)==0) return;
    copyFileToFolder(originPath,originName, newPath, newName);
    historyFromPath.push(originPath);
    historyFromName.push(originName);
    historyToPath.push(newPath);
    historyToName.push(newName);
    historyType.push_back("folder");
    deleteFile(originPath + "/" + originName);
}

void FileManager::moveFileToFolder(QString originPath, QString originName,QString newPath,QString rename,int digits) {
    copyFileToFolder(originPath,originName,newPath,rename,digits);
    deleteFile(originPath + "/" + originName);
}

QString FileManager::generateName(QString dest, QString rename, QString suffix,int digits) {
    QFileInfo* info = new QFileInfo(dest);
    QString name = rename;
    if(info->isDir()) {
        QDir dir(dest);    
        QStringList filter;
        filter << "*.jpeg" << "*.jpg" << "*.gif" << "*.png" << "*.tiff";
        QString fileCount = QString::number(dir.entryList(filter,QDir::Files).count()+1);
        if(fileCount.count()<digits) {
            int difference = digits - fileCount.count();
            for(int i=0;i<difference;i++) {
                fileCount.insert(0,"0");
            }
        }
        name.append(fileCount + "." + suffix);
    }
    delete info;
    return name;
}

void FileManager::undoChange() {
    if(historyFromName.count()==0) return;
    if(QString::compare(historyType.top(),"folder",Qt::CaseInsensitive)==0) {
        QFileInfo* from = new QFileInfo(historyFromPath.top() + "/" + historyFromName.top());
        QFileInfo* to = new QFileInfo(historyToPath.top() + "/" + historyToName.top());
        if(!from->exists()&&to->exists()) {
            QFile::copy(historyToPath.top() + "/" + historyToName.top(),from->absoluteFilePath());
            deleteFile(historyToPath.top() + "/" + historyToName.top());
        }
        delete from;
        delete to;
    }
    historyFromPath.pop();
    historyFromName.pop();
    historyToPath.pop();
    historyToName.pop();
    historyType.pop();
}
