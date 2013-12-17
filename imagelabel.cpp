#include "imagelabel.h"

#ifdef STATIC
Q_IMPORT_PLUGIN(qjpeg)
Q_IMPORT_PLUGIN(qtiff)
Q_IMPORT_PLUGIN(qgif)
#endif

ImageLabel::ImageLabel() {
    isThumbnail = true;
    pixmap = QPixmap();
    this->resize(0,0);
}

void ImageLabel::setImage(QString path) {
    filename = path;
    pixmap.load(path);
    if(isThumbnail) {
        QScrollArea *scroll = (QScrollArea*) parent();
        int view_height = scroll->viewport()->height();
        int view_width = scroll->viewport()->width();
        if(pixmap.height()>view_height||pixmap.width()>view_width) {
            if(pixmap.height()/2>view_height||pixmap.width()/2>view_width) {
                pixmap = pixmap.scaled(pixmap.width()/2,pixmap.height()/2,Qt::KeepAspectRatio,Qt::FastTransformation);
            }
            pixmap = pixmap.scaled(view_width,view_height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
    }
    this->resize(pixmap.width(),pixmap.height());
    this->setPixmap(pixmap);
}

void ImageLabel::clearImage() {
    this->clear();
    this->resize(0,0);
    filename = "";
}

void ImageLabel::refresh() {
    if(filename!="") setImage(filename);
}

void ImageLabel::thumbSwitch() {
    isThumbnail = !isThumbnail;
}
