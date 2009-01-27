#include "imagelabel.h"

Q_IMPORT_PLUGIN(qjpeg)
Q_IMPORT_PLUGIN(qtiff)
Q_IMPORT_PLUGIN(qgif)

ImageLabel::ImageLabel() {
    isThumbnail = true;
    pixmap = QPixmap();
    this->resize(0,0);
}

void ImageLabel::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_T) {
        isThumbnail = !isThumbnail;
    } else event->ignore();
}

void ImageLabel::setImage(QString path) {
    filename = path;
    pixmap.load(path);
    if(isThumbnail) {
        QScrollArea *scroll = (QScrollArea*) parent();
        int view_height = scroll->viewport()->height();
        int view_width = scroll->viewport()->width();
        if(pixmap.height()>view_height||pixmap.width()>view_height) {
            pixmap = pixmap.scaled(view_width,view_height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
    }
    this->resize(pixmap.width(),pixmap.height());
    this->setPixmap(pixmap);
}

void ImageLabel::clearImage() {
    QScrollArea *scroll = (QScrollArea*) parent();
    this->setPixmap(NULL);
    this->resize(0,0);
    filename = "";
}

void ImageLabel::refresh() {
    if(filename!="") setImage(filename);
}
