#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTextEdit>
#include <QWidget>
#include <QFile>

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
        QTabWidget *tab;
        QWidget *infoPane, *licensePane;
        QTextEdit *licenseEdit;

    public slots:
        void accept();

    signals:
};

#endif // ABOUTDIALOG_H
