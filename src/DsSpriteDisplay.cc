#include <QLabel>
#include "DsSpriteDisplay.h"

DsSpriteDisplay::DsSpriteDisplay(QWidget* parent)
	:QWidget(parent)
{
     QLabel* infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click toSpriteDisplaytoSpriteDisplay toSpriteDisplay toSpriteDisplay toSpriteDisplay toSpriteDisplay toSpriteDisplay  "
                               "invoke a context menu</i>"),this);
     infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
     infoLabel->setAlignment(Qt::AlignCenter);
}

