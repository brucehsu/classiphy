#include "aboutdialog.h"
#include "const.h"

AboutDialog::AboutDialog() {
    //Initialize objects.
    layout = new QVBoxLayout();
    infoLabel = new QLabel();
    okBtn = new QPushButton(QObject::trUtf8("Ok"));

    //Arrange objects.
    layout->addWidget(infoLabel,1,Qt::AlignHCenter);
    layout->addWidget(okBtn,1,Qt::AlignHCenter);

    //Set objects up.
    infoLabel->setAlignment(Qt::AlignHCenter);
    infoLabel->setTextFormat(Qt::RichText);
    infoLabel->setText("classiPHy v" + version + "<br />"
                       + QObject::trUtf8("Developed by Bruce Hsu.")
                       + "<br /><a href=\"" + website + "\">" + website + "</a>");
    okBtn->setMaximumWidth(90);

    //Connect slots and signals.
    QObject::connect(okBtn,SIGNAL(clicked()),SLOT(accept()));

    this->setModal(true);
    this->setLayout(layout);
    this->resize(150,80);
    this->setWindowTitle(QObject::trUtf8("About"));
    this->setMaximumHeight(80);
    this->setMaximumWidth(150);
}

void AboutDialog::accept() {
    this->close();
}
