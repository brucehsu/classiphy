#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QImage>
#include <QPixmap>
#include <QtPlugin>

class ImageLabel : public QLabel
{
    public:
        ImageLabel();
        void setImage(QString path);
        void clearImage();

    protected:
        void keyPressEvent(QKeyEvent*);
        //void resizeEvent(QResizeEvent*);

    private:
        bool isThumbnail;
        QPixmap pixmap;
        QString filename;
};

#endif // IMAGELABEL_H
