#include "filemanager.h"

FileManager::FileManager()
{
}

void FileManager::deleteFile(QString path) {
    QFile *originFile = new QFile(path);
    originFile->remove();
    delete originFile;
}

void FileManager::copyFileToFolder(QString originPath, QString originName,QString newPath,QString newName) {
    QFile *originFile = new QFile(originPath + "/" + originName);
    originFile->copy(newPath + "/" + newName);
    delete originFile;
}

void FileManager::copyFileToFolder(QString originPath, QString originName,QString newPath,QString rename,int digits) {
    QFileInfo* info = new QFileInfo(originPath + "/" + originName);
    QString name = generateName(newPath,rename,info->completeSuffix(),digits);
    copyFileToFolder(originPath,originName, newPath, name);
    delete info;
}

void FileManager::moveFileToFolder(QString originPath, QString originName,QString newPath,QString newName) {
    /*historyFromPath.push(originPath);
    historyFromName.push(originName);
    historyToPath.push(newPath);
    historyToName.push(newName);
    historyType.push_back("folder");*/
    copyFileToFolder(originPath,originName, newPath, newName);
    deleteFile(originPath + "/" + originName);
}

void FileManager::moveFileToFolder(QString originPath, QString originName,QString newPath,QString rename,int digits) {
    copyFileToFolder(originPath,originName,newPath,rename,digits);
    deleteFile(originPath + "/" + originName);
}

void FileManager::copyFileToZip(QString filePath, QString fileName, QString zipPath) {
    QuaZip zip(zipPath);
    QFileInfo* info = new QFileInfo(zipPath);
    if(!info->exists()) {
        zip.open(QuaZip::mdCreate);
        zip.close();
    }
    if(zip.open(QuaZip::mdAdd)) {
        zip.setFileNameCodec(QTextCodec::codecForName("utf8"));
        QFile* in = new QFile(filePath+"/"+fileName);
        in->open(QIODevice::ReadOnly);
        QuaZipFile out(&zip);
        out.open(QIODevice::WriteOnly,QuaZipNewInfo(in->fileName()));
        char c;
        while(in->getChar(&c)&&out.putChar(c));
        out.close();
        in->close();
        delete in;
    }
    zip.close();
    delete info;
}

void FileManager::copyFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits) {
    QFileInfo* info = new QFileInfo(filePath+"/"+fileName);
    QString name = generateName(fileName,rename,info->completeSuffix(),digits);
    copyFileToZip(filePath,name,zipPath);
    delete info;
}

void FileManager::moveFileToZip(QString filePath, QString fileName, QString zipPath) {
    copyFileToZip(filePath,fileName,zipPath);
    deleteFile(filePath);
}

void FileManager::moveFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits) {
    copyFileToZip(filePath,fileName,zipPath,rename,digits);
    deleteFile(filePath);
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
        QuaZip zip(dest);
        if(zip.open(QuaZip::mdAdd)) {
            zip.setFileNameCodec(QTextCodec::codecForName("utf8"));
        }
        QString fileCount = QString::number(zip.getEntriesCount()+1);
        if(fileCount.count()<digits) {
            int difference = digits - fileCount.count();
            for(int i=0;i<difference;i++) {
                fileCount.insert(0,"0");
            }
        }
        zip.close();
        name.append(fileCount + "." + suffix);
    }
    delete info;
    return name;
}
