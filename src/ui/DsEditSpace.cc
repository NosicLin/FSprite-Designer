#include <QLabel>
#include "DsEditSpace.h"


DsEditSpace::DsEditSpace(QWidget* parent)
    :QWidget(parent)
{


    QLabel* infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to EditSpace EditSpaceEditSpaceEditSpaceEditSpaceEditSpaceEditSpaceEditSpace"
                              "invoke a context menu</i>"),this);
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);



}
