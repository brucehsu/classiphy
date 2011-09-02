#ifndef NOSEARCHCOMBOBOX_H
#define NOSEARCHCOMBOBOX_H

#include <QComboBox>
#include <QKeyEvent>

class NoSearchComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit NoSearchComboBox(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:

};

#endif // NOSEARCHCOMBOBOX_H
