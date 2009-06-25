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
    historyFromPath.push(originPath);
    historyFromName.push(originName);
    historyToPath.push(newPath);
    historyToName.push(name);
    historyType.push_back("folder");
    delete info;
}

void FileManager::moveFileToFolder(QString originPath, QString originName,QString newPath,QString newName) {
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
    historyFromPath.push(filePath);
    historyFromName.push(fileName);
    historyToPath.push(zipPath);
    historyToName.push(name);
    historyType.push_back("zip");
    delete info;
}

void FileManager::moveFileToZip(QString filePath, QString fileName, QString zipPath) {
    copyFileToZip(filePath,fileName,zipPath);
    historyFromPath.push(filePath);
    historyFromName.push(fileName);
    historyToPath.push(zipPath);
    historyToName.push(fileName);
    historyType.push_back("zip");
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

void FileManager::undoChange() {
    if(QString::compare(historyType.top(),"folder",Qt::CaseInsensitive)==0) {
        QFileInfo* from = new QFileInfo(historyFromPath.top() + "/" + historyFromName.top());
        QFileInfo* to = new QFileInfo(historyToPath.top() + "/" + historyToName.top());
        if(!from->exists()&&to->exists()) {
            QFile::copy(historyToPath.top() + "/" + historyToName.top(),from->absoluteFilePath());
            deleteFile(historyToPath.top() + "/" + historyToName.top());
        }
        delete from;
        delete to;
    } else {
        QuaZip zip(historyToPath.top() + "/" + historyToName.top());
        QuaZipFile file(&zip);
        QuaZipFileInfo info;
        QFile out;
        char c;
        zip.setFileNameCodec(QTextCodec::codecForName("utf8"));
        for(bool more = zip.goToFirstFile();more;more = zip.goToNextFile()) {
            if(!zip.getCurrentFileInfo(&info)) {
                break;
            }
            if(QString::compare(info.name,historyToName.top())==0) {
                file.open(QIODevice::ReadOnly);
                out.setFileName(historyFromPath.top() + "/" + historyFromName.top());
                out.open(QIODevice::WriteOnly);
                while(file.getChar(&c)) out.putChar(c);
                out.close();
                break;
            }
        }
        file.close();
        zip.close();
    }
    historyFromPath.pop();
    historyFromName.pop();
    historyToPath.pop();
    historyToName.pop();
    historyType.pop();
}
