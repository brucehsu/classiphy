#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QStack>
#include <QFile>
#include <QDir>

class FileManager
{
    public:
        FileManager();
        void copyFileToFolder(QString originPath, QString originName,QString newPath,QString newName);
        void copyFileToFolder(QString originPath, QString originName,QString newPath,QString rename,int digits);
        void moveFileToFolder(QString originPath, QString originName,QString newPath,QString newName);
        void moveFileToFolder(QString originPath, QString originName,QString newPath,QString rename,int digits);
        void undoChange();

    protected:
        QString generateName(QString dest, QString rename, QString suffix,int digits);
        void deleteFile(QString path);

    private:
        QStack<QString> historyFromPath,historyFromName, historyToPath, historyToName,historyType;
};

#endif // FILEMANAGER_H
