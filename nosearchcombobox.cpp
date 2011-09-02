#include "nosearchcombobox.h"
#include "folderswindow.h"

NoSearchComboBox::NoSearchComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

void NoSearchComboBox::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Down||event->key()==Qt::Key_Up
       ||event->key()==Qt::Key_PageUp||event->key()==Qt::Key_PageDown
       ||event->key()==Qt::Key_Home||event->key()==Qt::Key_End
       || (event->modifiers() & Qt::ControlModifier)) {
        QComboBox::keyPressEvent(event);
        return;
    }
    ((FoldersWindow*) this->parentWidget())->processKeyEvent(event);
}

