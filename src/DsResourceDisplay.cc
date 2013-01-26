#include <QLabel>
#include <QVBoxLayout>

#include "DsResourceDisplay.h"



DsResourceDisplay::DsResourceDisplay(QWidget* p)
	:QWidget(p)
{


    QLabel* infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to DsResourceDisplay DsResourceDisplayDsResourceDisplayDsResourceDisplayDsResourceDisplayDsResourceDisplay"
                                      "invoke a context menu</i>"),this);
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);
    QLabel* infoLabel2 = new QLabel(tr("<i>Choose a menu option, or right-click to DsResourceDisplay DsResourceDisplayDsResourceDisplayDsResourceDisplayDsResourceDisplayDsResourceDisplay"
                                      "invoke a context menu</i>"),this);

    QLabel* infoLabel3 = new QLabel(tr("<i>Choose a menu option, or right-click to DsResourceDisplay DsResourceDisplayDsResourceDisplayDsResourceDisplayDsResourceDisplayDsResourceDisplay"
                                      "invoke a context menu</i>"),this);

    QVBoxLayout* hbox=new QVBoxLayout(this);

    hbox->addWidget(infoLabel,1);
    hbox->addWidget(infoLabel2,1);
    hbox->addWidget(infoLabel3,1);

    setLayout(hbox);


}


