#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QStack>
#include <QFile>
#include <QDir>
#include "third_party/quazip/quazip/quazip.h"
#include "third_party/quazip/quazip/quazipfile.h"

class FileManager
{
    public:
        FileManager();
        void deleteFile(QString path);
        void copyFileToFolder(QString originPath,QString newPath);
        void copyFileToFolder(QString originPath,QString newPath,QString rename,int digits);
        void moveFileToFolder(QString originPath,QString newPath);
        void moveFileToFolder(QString originPath,QString newPath,QString rename,int digits);
        void copyFileToZip(QString filePath, QString fileName, QString zipPath);
        void copyFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits);
        void moveFileToZip(QString filePath, QString fileName, QString zipPath);
        void moveFileToZip(QString filePath, QString fileName, QString zipPath,QString rename,int digits);
        void undoChange();

    protected:
        QString generateName(QString dest, QString rename, QString suffix,int digits);

    private:
        QStack<QString> historyFrom,historyTo,historyType;
};

#endif // FILEMANAGER_H
