#include "imagelabel.h"

Q_IMPORT_PLUGIN(qjpeg)
Q_IMPORT_PLUGIN(qtiff)
Q_IMPORT_PLUGIN(qgif)

ImageLabel::ImageLabel() {
    isThumbnail = true;
    pixmap = QPixmap();
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

    } else this->resize(pixmap.width(),pixmap.height());
    this->setPixmap(pixmap);
}

void ImageLabel::clearImage() {
    this->setPixmap(NULL);
    this->resize(0,0);
}
