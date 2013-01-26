#include <QLabel>
#include <QVBoxLayout>

#include "DsResourceDisplay.h"



DsResourceDisplay::DsResourceDisplay(QWidget* p)
	:QWidget(p)
{


    QLabel* infoLabel = new QLabel(tr("<i>Choose a menu option"),this);
    QLabel* infoLabel2 = new QLabel(tr("<i>Choose a menu optio"),this);

    QLabel* infoLabel3 = new QLabel(tr("<i>Choose a menu optio"),this);

    QVBoxLayout* hbox=new QVBoxLayout(this);

    hbox->addWidget(infoLabel,1);
    hbox->addWidget(infoLabel2,1);
    hbox->addWidget(infoLabel3,1);

    setLayout(hbox);


}


