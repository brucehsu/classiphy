#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QImage>
#include <QPixmap>
#include <QtPlugin>
#include <QScrollArea>

class ImageLabel : public QLabel
{
    public:
        ImageLabel();
        void setImage(QString path);
        void clearImage();
        void refresh();
        void thumbSwitch();

    protected:

    private:
        bool isThumbnail;
        QPixmap pixmap;
        QString filename;
};

#endif // IMAGELABEL_H
