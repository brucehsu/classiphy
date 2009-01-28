#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class AboutDialog : public QDialog
{
    Q_OBJECT
    public:
        AboutDialog();

    protected:

    private:
        QVBoxLayout *layout;
        QLabel *infoLabel;
        QPushButton *okBtn;

    public slots:
        void accept();

    signals:
};

#endif // ABOUTDIALOG_H
