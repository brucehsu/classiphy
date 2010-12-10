#include "aboutdialog.h"
#include "const.h"


AboutDialog::AboutDialog() {
    //Initialize objects.
    tab = new QTabWidget();
    layout = new QVBoxLayout();
    infoLabel = new QLabel();
    okBtn = new QPushButton(QObject::trUtf8("Ok"));
    licenseEdit = new QTextEdit();

    //Load license
    QFile *license = new QFile(":/LICENSE");
    license->open(QIODevice::ReadOnly | QIODevice::Text);

    //Set objects up.
    infoLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    infoLabel->setTextFormat(Qt::RichText);
    infoLabel->setText("classiPHy v" + version + "<br />Copyright (C) 2008-2011 Szu-Kai Hsu(Bruce Hsu)<br />"
                       + QObject::trUtf8("Licensed under General Public License Version 2") + "<br />"
                       + QObject::trUtf8("Developers: ") + authurs +
                       + "<br /><a href=\"" + website + "\">" + website + "</a>");
    okBtn->setMaximumWidth(90);
    licenseEdit->setReadOnly(true);
    licenseEdit->setLineWrapMode(QTextEdit::NoWrap);
    licenseEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    licenseEdit->setText(license->readAll());
    tab->setMinimumSize(400,200);

    //Arrange layout
    tab->addTab(infoLabel,QObject::trUtf8("Info"));
    tab->addTab(licenseEdit,QObject::trUtf8("License"));
    layout->addWidget(tab,2,Qt::AlignHCenter);
    layout->addWidget(okBtn,1,Qt::AlignHCenter);

    //Connect slots and signals.
    QObject::connect(okBtn,SIGNAL(clicked()),SLOT(accept()));

    this->setModal(true);
    this->setLayout(layout);
    this->resize(150,100);
    this->setWindowTitle(QObject::trUtf8("About"));
    this->setMaximumHeight(80);
    this->setMaximumWidth(150);

    license->close();
    delete license;
}

void AboutDialog::accept() {
    this->close();
}
