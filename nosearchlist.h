#ifndef NOSEARCHLIST_H
#define NOSEARCHLIST_H

#include <QListWidget>

class NoSearchList : public QListWidget
{
    public:
        NoSearchList(QWidget *parent);

    protected:
        virtual void keyboardSearch(const QString &search);
        void keyPressEvent(QKeyEvent *event);
};

#endif // NOSEARCHLIST_H
