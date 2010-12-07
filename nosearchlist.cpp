#include "nosearchlist.h"
#include "mainwindow.h"

NoSearchList::NoSearchList(QWidget *parent)
{
    this->setParent(parent);
}

void NoSearchList::keyboardSearch(const QString &search) {
    return;
}

void NoSearchList::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Down||event->key()==Qt::Key_Up) {
        QListWidget::keyPressEvent(event);
        return;
    }
    ((MainWindow*) this->parentWidget())->processKeyEvent(event);
}
