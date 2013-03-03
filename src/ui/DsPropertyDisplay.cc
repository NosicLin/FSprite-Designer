#include "DsPropertyDisplay.h"
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <float.h>
#include <QDebug>

#include "model/DsData.h"
#include "operator/DsDataOperator.h"
#include "operator/DsOperator.h"
#include "model/DsProject.h"
#include "model/DsFrameImage.h"
DsPropertyDisplay::DsPropertyDisplay(QWidget* parent)
	:QWidget(parent)
{
    createLayout();
    connectDsDataSignal();
    connectAllSpinBox();
}

void DsPropertyDisplay::connectAllSpinBox()
{
    //set FrameImage property
    //position
    connect(m_posXDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetPositon()));
    connect(m_posYDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetPositon()));

    //angle
    connect(m_angleSpinDoubleBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetAngle(double)));

    //scale
    connect(m_scaleXDoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetScale()));
    connect(m_scaleYDoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetScale()));

    //texture
    connect(m_textureX0DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));
    connect(m_textureY0DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));
    connect(m_textureX1DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));
    connect(m_textureY1DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));

    //offset
    connect(m_offsetXDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetOffset()));
    connect(m_offsetYDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetOffset()));

    //alpha
    connect(m_alphaDoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetAlpha(double)));
}

void DsPropertyDisplay::disconnectAllSpinBox()
{
    //position
    disconnect(m_posXDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetPositon()));
    disconnect(m_posYDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetPositon()));

    //angle
    disconnect(m_angleSpinDoubleBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetAngle(double)));

    //scale
    disconnect(m_scaleXDoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetScale()));
    disconnect(m_scaleYDoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetScale()));

    //texture
    disconnect(m_textureX0DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));
    disconnect(m_textureY0DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));
    disconnect(m_textureX1DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));
    disconnect(m_textureY1DoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetTextureArea()));

    //offset
    disconnect(m_offsetXDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetOffset()));
    disconnect(m_offsetYDoubleSpinbox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetOffset()));

    //alpha
    disconnect(m_alphaDoubleSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(slotSetAlpha(double)));
}
/* set position */
void DsPropertyDisplay::slotSetPositon()
{
    disconnectDsDataSignal();
    DsOperator::data()->setCurFrameImagePos(
                m_posXDoubleSpinbox->value(),
                m_posYDoubleSpinbox->value());
    connectDsDataSignal();
}

/* set angle */
void DsPropertyDisplay::slotSetAngle(double value)
{
    disconnectDsDataSignal();
    DsOperator::data()->setCurFrameImageAngle(value);
    connectDsDataSignal();
}

/* set scale */
void DsPropertyDisplay::slotSetScale()
{
    disconnectDsDataSignal();
    DsOperator::data()->setCurFrameImageScale(
                m_scaleXDoubleSpinBox->value(),
                m_scaleYDoubleSpinBox->value());
    connectDsDataSignal();
}


/* set texture */
void DsPropertyDisplay::slotSetTextureArea()
{
    disconnectDsDataSignal();
    DsOperator::data()->setCurFrameImageTextureArea(
                m_textureX0DoubleSpinBox->value(),
                m_textureY0DoubleSpinBox->value(),
                m_textureX1DoubleSpinBox->value(),
                m_textureY1DoubleSpinBox->value());
    connectDsDataSignal();
}

/* set offset */
void DsPropertyDisplay::slotSetOffset()
{
    disconnectDsDataSignal();
    DsOperator::data()->setCurFrameImageOffset(
                m_offsetXDoubleSpinbox->value(),
                m_offsetYDoubleSpinbox->value()
                );

    connectDsDataSignal();
}

/* set alpha */
void DsPropertyDisplay::slotSetAlpha(double value)
{
    disconnectDsDataSignal();
    DsOperator::data()->setCurFrameImageAlpha(value);
    connectDsDataSignal();
}
void DsPropertyDisplay::slotSetDoubleSpinBoxValue(int value)
{
    qDebug()<<"set double spin box value:"<<QString::number((double)value/1000000);
    m_alphaDoubleSpinBox->setValue((double)value/1000000);
}
void DsPropertyDisplay::slotSetSliderValue(double value)
{
    qDebug()<<"set slider value:"<<QString::number((int)(value*1000000));
    m_alphaSlider->setValue((int)(value*1000000));

}

void DsPropertyDisplay::slotFrameImagePropertyChange()
{
    DsProject* pro = DsData::shareData()->getProject();
    if(pro == NULL)
    {
        qDebug()<<"has no current project";
        return;
    }

   DsFrameImage* curFrameImage;
   curFrameImage = pro->getCurFrameImage();
   if(curFrameImage == NULL)
   {

       this->hide();
       return;
   }
   this->show();
   /* transform */
   float tx,ty;
   float sx,sy;
   float angle;

   /* texture area */
   float areax0,areay0;
   float areax1,areay1;

   /* alpha */
   float alpha;

   /* offset */
   float offx,offy;

   //get position
   tx = curFrameImage->getPosX();
   ty = curFrameImage->getPosY();

   //get scale
   sx = curFrameImage->getScaleX();
   sy = curFrameImage->getScaleY();

   //get angle
   angle = curFrameImage->getAngle();

   //get texture area
   curFrameImage->getTextureArea(&areax0,&areay0,&areax1,&areay1);

   //get alpha
   alpha = curFrameImage->getAlpha();

   //get offset
   offx = curFrameImage->getOffsetX();
   offy = curFrameImage->getOffsetY();


   disconnectAllSpinBox();
   //set attribute values to widgets
   m_posXDoubleSpinbox->setValue(tx);
   m_posYDoubleSpinbox->setValue(ty);

   m_scaleXDoubleSpinBox->setValue(sx);
   m_scaleYDoubleSpinBox->setValue(sy);

   m_angleSpinDoubleBox->setValue(angle);

   m_textureX0DoubleSpinBox->setValue(areax0);
   m_textureY0DoubleSpinBox->setValue(areay0);
   m_textureX1DoubleSpinBox->setValue(areax1);
   m_textureY1DoubleSpinBox->setValue(areay1);

   m_alphaDoubleSpinBox->setValue(alpha);

   m_offsetXDoubleSpinbox->setValue(offx);
   m_offsetYDoubleSpinbox->setValue(offy);

   connectAllSpinBox();
}


void DsPropertyDisplay::createLayout()
{
    int vLayoutSpace = 20;
    int indentation =30;
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(255,255,255));
    this->setPalette(palette);

    //===================================
    //setup mainLayout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMargins margins(30,11,30,50);
    mainLayout->setContentsMargins (margins);


    //1 setup position
    m_posLabel = new QLabel(tr("Position:"));
    m_posXLabel = new QLabel(tr("X:"));
    m_posYLabel = new QLabel(tr("Y:"));
    m_posXDoubleSpinbox = new QDoubleSpinBox(this);
    m_posYDoubleSpinbox = new QDoubleSpinBox(this);
    m_posXDoubleSpinbox->setDecimals(4);
    m_posXDoubleSpinbox->setRange(-DBL_MAX,DBL_MAX);
    m_posXDoubleSpinbox->setSingleStep(1);
    m_posYDoubleSpinbox->setDecimals(4);
    m_posYDoubleSpinbox->setRange(-DBL_MAX,DBL_MAX);
    m_posYDoubleSpinbox->setSingleStep(1);

    //2 setup angle
    m_angleLabel = new QLabel(tr("Rotate:"));
    m_angLabel = new QLabel(tr("Angle:"));
    m_angleSpinDoubleBox = new QDoubleSpinBox(this);
    m_angleSpinDoubleBox->setDecimals(4);
    m_angleSpinDoubleBox->setRange(-DBL_MAX,DBL_MAX);
    m_angleSpinDoubleBox->setSingleStep(1);


    //3 setup scale
    m_scaleLabel = new QLabel(tr("Scale:"));
    m_scaleXLabel = new QLabel(tr("SX:"));
    m_scaleYLabel = new QLabel(tr("SY:"));
    m_scaleXDoubleSpinBox = new QDoubleSpinBox(this);
    m_scaleYDoubleSpinBox = new QDoubleSpinBox(this);

    m_scaleXDoubleSpinBox->setDecimals(4);
    m_scaleXDoubleSpinBox->setRange(0,DBL_MAX);
    m_scaleXDoubleSpinBox->setSingleStep(0.05);

    m_scaleYDoubleSpinBox->setDecimals(4);
    m_scaleYDoubleSpinBox->setRange(0,DBL_MAX);
    m_scaleYDoubleSpinBox->setSingleStep(0.05);

    //4 setup TextureArea
    m_textureLabel = new QLabel(tr("TextureArea:"));
    m_textureX0Label = new QLabel(tr("TX0:"));
    m_textureY0Label = new QLabel(tr("TY0:"));
    m_textureX1Label = new QLabel(tr("TX1:"));
    m_textureY1Label = new QLabel(tr("TY1:"));

    m_textureX0DoubleSpinBox = new QDoubleSpinBox(this);
    m_textureY0DoubleSpinBox = new QDoubleSpinBox(this);
    m_textureX1DoubleSpinBox = new QDoubleSpinBox(this);
    m_textureY1DoubleSpinBox = new QDoubleSpinBox(this);

    m_textureX0DoubleSpinBox->setDecimals(6);
    m_textureX0DoubleSpinBox->setRange(0,1);
    m_textureX0DoubleSpinBox->setSingleStep(0.05);
    m_textureY0DoubleSpinBox->setDecimals(6);
    m_textureY0DoubleSpinBox->setRange(0,1);
    m_textureY0DoubleSpinBox->setSingleStep(0.05);

    m_textureX1DoubleSpinBox->setDecimals(6);
    m_textureX1DoubleSpinBox->setRange(0,1);
    m_textureX1DoubleSpinBox->setSingleStep(0.05);
    m_textureY1DoubleSpinBox->setDecimals(6);
    m_textureY1DoubleSpinBox->setRange(0,1);
    m_textureY1DoubleSpinBox->setSingleStep(0.05);

    //5 setup offset
    m_offsetLabel = new QLabel(tr("Offset:"));
    m_offsetXLabel = new QLabel(tr("X:"));
    m_offsetYLabel = new QLabel(tr("Y:"));
    m_offsetXDoubleSpinbox = new QDoubleSpinBox(this);
    m_offsetYDoubleSpinbox = new QDoubleSpinBox(this);
    m_offsetXDoubleSpinbox->setDecimals(4);
    m_offsetXDoubleSpinbox->setRange(-DBL_MAX,DBL_MAX);
    m_offsetXDoubleSpinbox->setSingleStep(1);
    m_offsetYDoubleSpinbox->setDecimals(4);
    m_offsetYDoubleSpinbox->setRange(-DBL_MAX,DBL_MAX);
    m_offsetYDoubleSpinbox->setSingleStep(1);

    //6 setup alpha
    m_alphaLabel = new QLabel(tr("Transparent:"));
    m_alLabel = new QLabel(tr("Alpha:"));
    m_alphaDoubleSpinBox = new QDoubleSpinBox(this);
    m_alphaDoubleSpinBox->setDecimals(6);
    m_alphaDoubleSpinBox->setRange(0.0,1.0);
    m_alphaDoubleSpinBox->setSingleStep(0.1);
    m_alphaSlider = new QSlider(Qt::Horizontal);
    m_alphaSlider->setRange(0,1000000);
    //1 setup position layout
    QVBoxLayout* posMainLayout = new QVBoxLayout;
    QGridLayout* posButtonLayout = new QGridLayout;
    //posButtonLayout->setRowStretch(0,0);
    posButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing

    posButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    posButtonLayout->addWidget(m_posXLabel,0,1,1,1,Qt::AlignRight);
    posButtonLayout->addWidget(m_posXDoubleSpinbox,0,2,1,3);
    posButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    posButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    posButtonLayout->addWidget(m_posYLabel,1,1,1,1);
    posButtonLayout->addWidget(m_posYDoubleSpinbox,1,2,1,3);
    posButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    posMainLayout->addWidget(m_posLabel);
    posMainLayout->addLayout(posButtonLayout);
    posMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(posMainLayout);

    //2 setup angle layout
    QVBoxLayout* angMainLayout = new QVBoxLayout;
    QHBoxLayout* angButtonLayout = new QHBoxLayout;
    angButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing
    angButtonLayout->addItem(new QSpacerItem(indentation-25,0));
    angButtonLayout->addWidget(m_angLabel,1);
    angButtonLayout->addWidget(m_angleSpinDoubleBox,2);
    angButtonLayout->addStretch(2);

    angMainLayout->addWidget(m_angleLabel);
    angMainLayout->addLayout(angButtonLayout);
    angMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(angMainLayout);

    //3 setup scale layout
    QVBoxLayout* scaleMainLayout = new QVBoxLayout;
    QGridLayout* scaleButtonLayout = new QGridLayout;
   // scaleButtonLayout->setRowStretch(0,0);
    scaleButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing
    scaleButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    scaleButtonLayout->addWidget(m_scaleXLabel,0,1,1,1);
    scaleButtonLayout->addWidget(m_scaleXDoubleSpinBox,0,2,1,3);
    scaleButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    scaleButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    scaleButtonLayout->addWidget(m_scaleYLabel,1,1,1,1);
    scaleButtonLayout->addWidget(m_scaleYDoubleSpinBox,1,2,1,3);
    scaleButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    scaleMainLayout->addWidget(m_scaleLabel);
    scaleMainLayout->addLayout(scaleButtonLayout);
    scaleMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(scaleMainLayout);

    //4 setup TextureArea layout
    QVBoxLayout* textureMainLayout = new QVBoxLayout;
    QGridLayout* textureButtonLayout = new QGridLayout;
  //  textureButtonLayout->setRowStretch(0,0);
    textureButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    textureButtonLayout->addWidget(m_textureX0Label,0,1,1,1);
    textureButtonLayout->addWidget(m_textureX0DoubleSpinBox,0,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    textureButtonLayout->addWidget(m_textureY0Label,1,1,1,1);
    textureButtonLayout->addWidget(m_textureY0DoubleSpinBox,1,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),2,0,1,1);
    textureButtonLayout->addWidget(m_textureX1Label,2,1,1,1);
    textureButtonLayout->addWidget(m_textureX1DoubleSpinBox,2,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),2,3,1,10);

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),3,0,1,1);
    textureButtonLayout->addWidget(m_textureY1Label,3,1,1,1);
    textureButtonLayout->addWidget(m_textureY1DoubleSpinBox,3,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),3,3,1,10);

    textureMainLayout->addWidget(m_textureLabel);
    textureMainLayout->addLayout(textureButtonLayout);
    textureMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(textureMainLayout);

    //5 setup offset layout
    QVBoxLayout* offsetMainLayout = new QVBoxLayout;
    QGridLayout* offsetButtonLayout = new QGridLayout;
   // offsetButtonLayout->setRowStretch(0,0);
    offsetButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing

    offsetButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    offsetButtonLayout->addWidget(m_offsetXLabel,0,1,1,1);
    offsetButtonLayout->addWidget(m_offsetXDoubleSpinbox,0,2,1,3);
    offsetButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    offsetButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    offsetButtonLayout->addWidget(m_offsetYLabel,1,1,1,1);
    offsetButtonLayout->addWidget(m_offsetYDoubleSpinbox,1,2,1,3);
    offsetButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    offsetMainLayout->addWidget(m_offsetLabel);
    offsetMainLayout->addLayout(offsetButtonLayout);
    offsetMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(offsetMainLayout);

    //6 setup alpha layout
    QVBoxLayout* alphaMainLayout = new QVBoxLayout();
    QHBoxLayout* alphaButtonLayout = new QHBoxLayout();
    alphaButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing
    alphaButtonLayout->addItem(new QSpacerItem(indentation-30,0));
    alphaButtonLayout->addWidget(m_alLabel,1);
    alphaButtonLayout->addWidget(m_alphaDoubleSpinBox,3);
    alphaButtonLayout->addWidget(m_alphaSlider,10);
    alphaButtonLayout->addStretch(1);

    alphaMainLayout->addWidget(m_alphaLabel);
    alphaMainLayout->addLayout(alphaButtonLayout);
    alphaMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(alphaMainLayout);

    mainLayout->addStretch();
    this->setLayout(mainLayout);

    connect(m_alphaDoubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(slotSetSliderValue(double)));
    connect(m_alphaSlider,SIGNAL(valueChanged(int)),this,SLOT(slotSetDoubleSpinBoxValue(int)));
    m_alphaDoubleSpinBox->setValue(0.0);

}

void DsPropertyDisplay::connectDsDataSignal()
{
    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotFrameImagePropertyChange()));
    connect(DsData::shareData(),SIGNAL(signalCurSpriteChange()),
            this,SLOT(slotFrameImagePropertyChange()));
    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotFrameImagePropertyChange()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameChange()),
            this,SLOT(slotFrameImagePropertyChange()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameImageChange()),
            this,SLOT(slotFrameImagePropertyChange()));

    connect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
            this,SLOT(slotFrameImagePropertyChange()));
    connect(DsData::shareData(),SIGNAL(signalAnimationPropertyChange()),
            this,SLOT(slotFrameImagePropertyChange()));
    connect(DsData::shareData(),SIGNAL(signalFramePropertyChange()),
            this,SLOT(slotFrameImagePropertyChange()));
    connect(DsData::shareData(),SIGNAL(signalFrameImagePropertyChange()),
            this,SLOT(slotFrameImagePropertyChange()));
}

void DsPropertyDisplay::disconnectDsDataSignal()
{
    disconnect(DsData::shareData(),0,this,0);
}
