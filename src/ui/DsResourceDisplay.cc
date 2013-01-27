#include <QLabel>
#include <QVBoxLayout>

#include "DsResourceDisplay.h"



DsResourceDisplay::DsResourceDisplay(QWidget* p)
	:QWidget(p)
{


    /* TODO(use real tree widget here */
    QLabel* tree= new QLabel(tr("Tree Control List\n  Folder1\n    File1.jpe\n    File2.png\n  Folder2\n    File1.bmp\n    File2.tga\n"),this);

    /* TODO(use your control here)*/
    QLabel* controlbar= new QLabel(tr(" ----------------\n|<add>| <delete> |\n ----------------"),this);


    QVBoxLayout* hbox=new QVBoxLayout(this);

    hbox->addWidget(tree,1,Qt::AlignTop);
    hbox->addWidget(controlbar,0);

    setLayout(hbox);


}


