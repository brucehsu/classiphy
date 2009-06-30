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

void FileManager::copyFileToZip(QString filePath, QString fileName, QString zipPath, QString insideName) {
    QuaZip zip(zipPath);
    QFileInfo* info = new QFileInfo(zipPath);
    if(!info->exists()) {
        zip.open(QuaZip::mdCreate);
    } else {
        zip.open(QuaZip::mdAdd);
    }
    if(zip.getZipError()==UNZ_OK) {
        zip.setFileNameCodec(QTextCodec::codecForName("utf8"));
        QFile* in = new QFile(filePath+"/"+fileName);
        in->open(QIODevice::ReadOnly);
        QuaZipFile out(&zip);
        out.open(QIODevice::WriteOnly,QuaZipNewInfo(insideName));
        char c;
        while(in->getChar(&c)&&out.putChar(c));
        out.close();
        in->close();
        delete in;
        zip.close();
    }
    delete info;
}

void FileManager::copyFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits) {
    QFileInfo* info = new QFileInfo(filePath+"/"+fileName);
    QString name = generateName(zipPath,rename,info->completeSuffix(),digits);
    copyFileToZip(filePath,fileName,zipPath,name);
    historyFromPath.push(filePath);
    historyFromName.push(fileName);
    historyToPath.push(zipPath);
    historyToName.push(name);
    historyType.push_back("zip");
    delete info;
}

void FileManager::moveFileToZip(QString filePath, QString fileName, QString zipPath) {
    copyFileToZip(filePath,fileName,zipPath,fileName);
    historyFromPath.push(filePath);
    historyFromName.push(fileName);
    historyToPath.push(zipPath);
    historyToName.push(fileName);
    historyType.push_back("zip");
    deleteFile(filePath + "/" + fileName);
}

void FileManager::moveFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits) {
    copyFileToZip(filePath,fileName,zipPath,rename,digits);
    deleteFile(filePath + "/" + fileName);
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
        QString fileCount;
        if(!info->exists()) {
            fileCount = QString::number(1);
        } else {
            zip.open(QuaZip::mdUnzip);
            zip.setFileNameCodec(QTextCodec::codecForName("utf8"));
            fileCount = QString::number(zip.getEntriesCount()+1);
            zip.close();
        }
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
    } else {
        QuaZip zip(historyToPath.top());
        QuaZipFile file(&zip);
        QuaZipFileInfo info;
        QFile out;
        char c;
        QString tmp = historyToPath.top() + "/" + historyToName.top();
        zip.open(QuaZip::mdUnzip);
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
        zip.close();
        deleteFileInZip(historyToPath.top(),historyToName.top());
    }
    historyFromPath.pop();
    historyFromName.pop();
    historyToPath.pop();
    historyToName.pop();
    historyType.pop();
}

void FileManager::deleteFileInZip(QString zipPath, QString insideName) {
    if(!QFile::exists(zipPath)) return;
    QuaZip zip(zipPath),tzip(zipPath+".tmp");
    zip.open(QuaZip::mdUnzip);
    tzip.open(QuaZip::mdCreate);
    QuaZipFile origin(&zip);
    QuaZipFileInfo info;
    char c;
    int fcount = 0;
    zip.setFileNameCodec(QTextCodec::codecForName("utf8"));
    for(bool more = zip.goToFirstFile();more;more = zip.goToNextFile()) {
        if(!zip.getCurrentFileInfo(&info)) {
            break;
        }
        if(QString::compare(info.name,insideName)!=0) {
            origin.open(QIODevice::ReadOnly);
            QuaZipFile tmp(&tzip);
            tmp.open(QIODevice::WriteOnly,QuaZipNewInfo(info.name));
            while(origin.getChar(&c)&&tmp.putChar(c)) ;
            origin.close();
            tmp.close();
            fcount++;
            tzip.close();
            tzip.open(QuaZip::mdAdd);
        }
    }
    zip.close();
    tzip.close();
    QFile::remove(zipPath);
    if(fcount==0) {
        QFile::remove(zipPath+".tmp");
    } else {
        QFile::rename(zipPath+".tmp",zipPath);
    }
}
