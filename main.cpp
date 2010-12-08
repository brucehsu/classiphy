#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/classiphy");
    a.installTranslator(&translator);
    MainWindow *main = new MainWindow();
    return a.exec();
}
