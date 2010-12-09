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
    if(event->key()==Qt::Key_Down||event->key()==Qt::Key_Up
       ||event->key()==Qt::Key_PageUp||event->key()==Qt::Key_PageDown
       ||event->key()==Qt::Key_Home||event->key()==Qt::Key_End
       || (event->modifiers() & Qt::ControlModifier)) {
        QListWidget::keyPressEvent(event);
        return;
    }
    ((MainWindow*) this->parentWidget())->processKeyEvent(event);
}
