#include "DsPropertyDisplay.h"
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <float.h>
#include <QDebug>
#include <QHeaderView>
#include "model/DsData.h"
#include "operator/DsDataOperator.h"
#include "operator/DsOperator.h"
#include "model/DsProject.h"
#include "model/DsFrameImage.h"

#include <stdio.h>
#include <string>
#define BG_RGB(r,g,b) ((r),(g),(b))
#define PALETTE_BASE_COLOR 255,255,222,255
#define PALETTE_ALT_BASE_COLOR 255,255,191,255

DsPropertyDisplay::DsPropertyDisplay(QWidget* parent)
	:QWidget(parent)
{
    initProperty();
    connectDsDataSignal();
}

void DsPropertyDisplay::initProperty()
{
    //user-defined palette for view
    QPalette pal;
    pal.setBrush(QPalette::Base,QBrush(QColor(PALETTE_BASE_COLOR)));
    pal.setBrush(QPalette::AlternateBase,QBrush(QColor(PALETTE_ALT_BASE_COLOR)));

    //view
    m_view = new QTreeView(this);
    //m_view.setMidLineWidth(10);
    m_view->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_view->setPalette(pal);
    m_view->setAlternatingRowColors(true);
    m_view->setHeaderHidden(false);
    m_view->header()->setResizeMode(QHeaderView::ResizeToContents);
    m_view->header()->setMovable(false);
   // QMargins margins(30,30,30,30);
    //this->setContentsMargins(margins);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMargins margins(11,11,11,11);
    mainLayout->setContentsMargins (margins);
    mainLayout->addWidget(m_view);
    this->setLayout(mainLayout);
    this->setDisabled(true);

    //set model
    m_model = new QStandardItemModel;
//    QStringList header_list;
   // header_list<<"Property"<<"Value";
    m_model->setColumnCount(2);
   // m_model->setHorizontalHeaderLabels(header_list);
    QStandardItem* propertyItem = new QStandardItem("Property");
    QStandardItem* ValueItem = new QStandardItem("Value");
    propertyItem->setDragEnabled(false);
    ValueItem->setDragEnabled(false);
    m_model->setHorizontalHeaderItem(0,propertyItem);
    m_model->setHorizontalHeaderItem(1,ValueItem);


    m_delegate = new DsDelegate(this);

    //config view
    m_view->setModel(m_model);
    m_view->setItemDelegate(m_delegate);
    //QStandardItem* root_item = m_model->invisibleRootItem();

    FrameAttr attr_type;

    double a = -100.00000001234;
    char str[20] = {0};
    sprintf(str,"%.6f",a);
    double variant = atof(str);

   // QString variant =  QString::fromLocal8Bit(str);

    m_posItem = new QStandardItem("Position:");
    m_posEmptyItem = new QStandardItem("");
    m_posXItem = new QStandardItem("x:");
    m_posYItem = new QStandardItem("y:");
    m_posItem->setEditable(false);
    m_posEmptyItem->setEditable(false);
    m_posXItem->setEditable(false);
    m_posYItem->setEditable(false);

    m_posXValueItem = new QStandardItem();
    attr_type = POSITION_X;
    m_posXValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_posXValueItem->setData(variant,Qt::EditRole);
    m_posYValueItem = new QStandardItem();
    attr_type = POSITION_Y;
    m_posYValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_posYValueItem->setData(variant,Qt::EditRole);


    QList<QStandardItem*> list;
    list<<m_posItem<<m_posEmptyItem;
    m_model->appendRow(list);
    list.clear();

    list<<m_posXItem<<m_posXValueItem;
    m_posItem->appendRow(list);
    list.clear();

    list<<m_posYItem<<m_posYValueItem;
    m_posItem->appendRow(list);
    list.clear();


    //init Rotate
    m_rotateItem = new QStandardItem("Rotate:");
    m_rotateEmptyItem = new QStandardItem("");
    m_angleItem = new QStandardItem("angle:");
    m_angleValueItem = new QStandardItem();
    attr_type = ROTATE;
    m_angleValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_angleValueItem->setData(variant,Qt::EditRole);

    m_rotateItem->setEditable(false);
    m_rotateEmptyItem->setEditable(false);
    m_angleItem->setEditable(false);

    list<<m_rotateItem<<m_rotateEmptyItem;
    m_model->appendRow(list);
    list.clear();

    list<<m_angleItem<<m_angleValueItem;
    m_rotateItem->appendRow(list);
    list.clear();

    //init Scale
    m_scaleItem = new QStandardItem("Scale:");
    m_scaleEmptyItem = new QStandardItem("");
    m_scaleXItem = new QStandardItem("x:");
    m_scaleYItem = new QStandardItem("y:");
    m_scaleXValueItem = new QStandardItem();
    attr_type = SCALE_X;
    m_scaleXValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_scaleXValueItem->setData(variant,Qt::EditRole);
    m_scaleYValueItem = new QStandardItem();
    attr_type = SCALE_Y;
    m_scaleYValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_scaleYValueItem->setData(variant,Qt::EditRole);

    m_scaleItem->setEditable(false);
    m_scaleEmptyItem->setEditable(false);
    m_scaleXItem->setEditable(false);
    m_scaleYItem->setEditable(false);

    list<<m_scaleItem<<m_scaleEmptyItem;
    m_model->appendRow(list);
    list.clear();

    list<<m_scaleXItem<<m_scaleXValueItem;
    m_scaleItem->appendRow(list);
    list.clear();

    list<<m_scaleYItem<<m_scaleYValueItem;
    m_scaleItem->appendRow(list);
    list.clear();

    //init texture
    m_textureItem = new QStandardItem("Texture:");
    m_textureEmptyItem = new QStandardItem("");
    m_textureX0Item = new QStandardItem("x0:");
    m_textureY0Item = new QStandardItem("y0:");
    m_textureX1Item = new QStandardItem("x1:");
    m_textureY1Item = new QStandardItem("y1:");
    m_textureX0ValueItem = new QStandardItem();
    attr_type = TEXTURE_X0;
    m_textureX0ValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_textureX0ValueItem->setData(variant,Qt::EditRole);
    m_textureY0ValueItem = new QStandardItem();
    attr_type = TEXTURE_Y0;
    m_textureY0ValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_textureY0ValueItem->setData(variant,Qt::EditRole);
    m_textureX1ValueItem = new QStandardItem();
    attr_type = TEXTURE_X1;
    m_textureX1ValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_textureX1ValueItem->setData(variant,Qt::EditRole);
    m_textureY1ValueItem = new QStandardItem();
    attr_type = TEXTURE_Y1;
    m_textureY1ValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_textureY1ValueItem->setData(variant,Qt::EditRole);

    m_textureItem->setEditable(false);
    m_textureEmptyItem->setEditable(false);
    m_textureX0Item->setEditable(false);
    m_textureY0Item->setEditable(false);
    m_textureX1Item->setEditable(false);
    m_textureY1Item->setEditable(false);

    list<<m_textureItem<<m_textureEmptyItem;
    m_model->appendRow(list);
    list.clear();

    list<<m_textureX0Item<<m_textureX0ValueItem;
    m_textureItem->appendRow(list);
    list.clear();

    list<<m_textureY0Item<<m_textureY0ValueItem;
    m_textureItem->appendRow(list);
    list.clear();

    list<<m_textureX1Item<<m_textureX1ValueItem;
    m_textureItem->appendRow(list);
    list.clear();

    list<<m_textureY1Item<<m_textureY1ValueItem;
    m_textureItem->appendRow(list);
    list.clear();


    //init offset
    m_offsetItem = new QStandardItem("Offset:");
    m_offsetEmptyItem = new QStandardItem("");
    m_offsetXItem = new QStandardItem("x:");
    m_offsetYItem = new QStandardItem("y:");
    m_offsetXValueItem = new QStandardItem();
    attr_type = OFFSET_X;
    m_offsetXValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_offsetXValueItem->setData(variant,Qt::EditRole);
    m_offsetYValueItem = new QStandardItem();
    attr_type = OFFSET_Y;
    m_offsetYValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_offsetYValueItem->setData(variant,Qt::EditRole);

    m_offsetItem->setEditable(false);
    m_offsetEmptyItem->setEditable(false);
    m_offsetXItem->setEditable(false);
    m_offsetYItem->setEditable(false);

    list<<m_offsetItem<<m_offsetEmptyItem;
    m_model->appendRow(list);
    list.clear();

    list<<m_offsetXItem<<m_offsetXValueItem;
    m_offsetItem->appendRow(list);
    list.clear();

    list<<m_offsetYItem<<m_offsetYValueItem;
    m_offsetItem->appendRow(list);
    list.clear();

    //init alpha
    m_transItem = new QStandardItem("Transparent:");
    m_transEmptyItem = new QStandardItem("");
    m_alphaItem = new QStandardItem("alpha:");
    m_alphaValueItem = new QStandardItem();
    attr_type = ALPHA;
    m_alphaValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_alphaValueItem->setData(variant,Qt::EditRole);

    m_transItem->setEditable(false);
    m_transEmptyItem->setEditable(false);
    m_alphaItem->setEditable(false);

    list<<m_transItem<<m_transEmptyItem;
    m_model->appendRow(list);
    list.clear();

    list<<m_alphaItem<<m_alphaValueItem;
    m_transItem->appendRow(list);
    list.clear();

    //init fps
    m_fpsItem = new QStandardItem("fps:");
    m_fpsValueItem = new QStandardItem();
    attr_type = FPS;
    m_fpsValueItem->setData(QVariant(attr_type),Qt::UserRole);
    m_fpsValueItem->setData(variant,Qt::EditRole);

    m_fpsItem->setEditable(false);
    list<<m_fpsItem<<m_fpsValueItem;
    m_model->appendRow(list);
    list.clear();

}

void DsPropertyDisplay::slotFrameImagePropertyChange()
{
    DsProject* pro = DsData::shareData()->getProject();
    if(pro == NULL)
    {
        qDebug()<<"has no current project";
        this->setDisabled(true);
        return;
    }
   DsAnimation* curAnimation = pro->getCurAnimation();
   if(NULL == curAnimation)
   {
       this->setDisabled(true);
       return;
   }
   int fps = curAnimation->getFps();
   m_fpsValueItem->setData(fps,Qt::EditRole);

   DsFrameImage* curFrameImage;
   curFrameImage = pro->getCurFrameImage();
   if(curFrameImage == NULL)
   {

       //this->hide();
       this->setDisabled(true);
       return;
   }
   qDebug()<<"in slotFrameImagePropertyChange";
   this->setEnabled(true);
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

   //position
   char str[20];
   double d_tx = tx;
   sprintf(str,"%.6f",d_tx);
   d_tx = atof(str);
   m_posXValueItem->setData(d_tx,Qt::EditRole);
   double d_ty = ty;
   sprintf(str,"%.6f",d_ty);
   d_ty = atof(str);
   m_posYValueItem->setData(d_ty,Qt::EditRole);

   //rotate
   double d_angle = angle;
   sprintf(str,"%.6f",d_angle);
   d_angle = atof(str);
   m_angleValueItem->setData(d_angle,Qt::EditRole);

   //scale
   double d_sx = sx;
   sprintf(str,"%.6f",d_sx);
   d_sx = atof(str);
   m_scaleXValueItem->setData(d_sx,Qt::EditRole);
   double d_sy = sy;
   sprintf(str,"%.6f",d_sy);
   d_sy = atof(str);
   m_scaleYValueItem->setData(d_sy,Qt::EditRole);

   //texture
   double d_areax0 = areax0;
   sprintf(str,"%.6f",d_areax0);
   d_areax0 = atof(str);
   m_textureX0ValueItem->setData(d_areax0,Qt::EditRole);
   double d_areay0 = areay0;
   sprintf(str,"%.6f",d_areay0);
   d_areay0 = atof(str);
   m_textureY0ValueItem->setData(d_areay0,Qt::EditRole);
   double d_areax1 = areax1;
   sprintf(str,"%.6f",d_areax1);
   d_areax1 = atof(str);
   m_textureX1ValueItem->setData(d_areax1,Qt::EditRole);
   double d_areay1 = areay1;
   sprintf(str,"%.6f",d_areay1);
   d_areay1 = atof(str);
   m_textureY1ValueItem->setData(d_areay1,Qt::EditRole);

   //offset
   double d_offx = offx;
   sprintf(str,"%.6f",d_offx);
   d_offx = atof(str);
   m_offsetXValueItem->setData(d_offx,Qt::EditRole);
   double d_offy = offy;
   sprintf(str,"%.6f",d_offy);
   d_offy = atof(str);
   m_offsetYValueItem->setData(d_offy,Qt::EditRole);
  // connectAllSpinBox();

   //alpha
   double d_alpha = alpha;
   sprintf(str,"%.6f",d_alpha);
   d_alpha = atof(str);
   m_alphaValueItem->setData(d_alpha,Qt::EditRole);
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
