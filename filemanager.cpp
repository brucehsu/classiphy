#include "filemanager.h"

FileManager::FileManager()
{
}

void FileManager::deleteFile(QString path) {
    QFile *originFile = new QFile(path);
    originFile->remove();
    delete originFile;
}

void FileManager::copyFileToFolder(QString originPath, QString newPath) {
    QFile *originFile = new QFile(originPath);
    originFile->copy(newPath);
    delete originFile;
}

void FileManager::copyFileToFolder(QString originPath, QString newPath,QString rename,int digits) {
    QFileInfo* info = new QFileInfo(originPath);
    QString name = generateName(newPath,rename,info->completeSuffix(),digits);
    copyFileToFolder(originPath,newPath + "/" + name);
    delete info;
}

void FileManager::moveFileToFolder(QString originPath, QString newPath) {
    historyFrom.push_back(originPath);
    historyTo.push_back(newPath);
    historyType.push_back("folder");
    copyFileToFolder(originPath, newPath);
    deleteFile(originPath);
}

void FileManager::moveFileToFolder(QString originPath, QString newPath,QString rename,int digits) {
    copyFileToFolder(originPath,newPath,rename,digits);
    deleteFile(originPath);
}

void FileManager::copyFileToZip(QString filePath, QString fileName, QString zipPath) {

}

void FileManager::copyFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits) {

}

void FileManager::moveFileToZip(QString filePath, QString fileName, QString zipPath) {

}

void FileManager::moveFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits) {

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
    } else {

    }
    delete info;
    return name;
}
