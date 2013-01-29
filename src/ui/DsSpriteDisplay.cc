#include <QLabel>
#include "DsSpriteDisplay.h"

DsSpriteDisplay::DsSpriteDisplay(QWidget* parent)
	:QWidget(parent)
{
     QLabel* infoLabel = new QLabel(tr("\n\n  Sprite1                \n  Sprite2\n  Sprite3\n  Sprite4"),this);
     //infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
     infoLabel->setAlignment(Qt::AlignCenter);
}

