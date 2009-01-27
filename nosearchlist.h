#ifndef NOSEARCHLIST_H
#define NOSEARCHLIST_H

#include <QListWidget>

class NoSearchList : public QListWidget
{
    public:
        NoSearchList();

    protected:
        virtual void keyboardSearch(const QString &search);
};

#endif // NOSEARCHLIST_H
