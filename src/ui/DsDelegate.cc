#include "DsDelegate.h"
#include <QDebug>
#include <QStandardItem>
#include <float.h>
#include <assert.h>
#include "operator/DsDataOperator.h"
#include "operator/DsOperator.h"
#include "DsPropertyDisplay.h"
double DsDelegate::m_preData = 0.0;
DsDelegate::DsDelegate(DsPropertyDisplay* view,QObject* parent )
    :QItemDelegate(parent)
{
    m_view = view;
}
QWidget *DsDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem & option ,
    const QModelIndex & index ) const
{

    qDebug()<<"in DsDelegate::createEditor";
   if(index.internalPointer()!= NULL)
   {
       QStandardItem* item = static_cast<QStandardItem*>(index.internalPointer());
        qDebug()<<item->data(Qt::EditRole).toString();
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);

        DsPropertyDisplay::FrameAttr attr_type = static_cast<DsPropertyDisplay::FrameAttr>(index.data(Qt::UserRole).toInt()); 
        if(attr_type == DsPropertyDisplay::POSITION_X
           ||attr_type == DsPropertyDisplay::POSITION_Y
           ||attr_type == DsPropertyDisplay::ROTATE)
        {
            editor->setDecimals(6);
            editor->setRange(-DBL_MAX,DBL_MAX);
            editor->setSingleStep(1);
        }
        else if(attr_type == DsPropertyDisplay::SCALE_X
                ||attr_type == DsPropertyDisplay::SCALE_Y)
        {
            editor->setDecimals(6);
            editor->setRange(0,DBL_MAX);
            editor->setSingleStep(0.05);
        }
        else if(attr_type == DsPropertyDisplay::TEXTURE_X0
                ||attr_type == DsPropertyDisplay::TEXTURE_Y0
                ||attr_type == DsPropertyDisplay::TEXTURE_X1
                ||attr_type == DsPropertyDisplay::TEXTURE_Y1)
        {
            editor->setDecimals(6);
            editor->setRange(0,1);
            editor->setSingleStep(0.05);
        }
        else if(attr_type == DsPropertyDisplay::OFFSET_X
                ||attr_type == DsPropertyDisplay::OFFSET_Y)
        {
            editor->setDecimals(6);
            editor->setRange(-DBL_MAX,DBL_MAX);
            editor->setSingleStep(1);
        }
        else if(attr_type == DsPropertyDisplay::OFFSET_X)
        {
            editor->setDecimals(6);
            editor->setRange(0.0,1.0);
            editor->setSingleStep(0.1);
        }
        else if(attr_type == DsPropertyDisplay::FPS)
        {
            editor->setDecimals(0);
            editor->setRange(0,DBL_MAX);
            editor->setSingleStep(1);
        }
        return editor;
    }
    return NULL;
}

void DsDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->setValue(index.data(Qt::EditRole).toDouble());
    m_preData = doubleSpinBox->value();
    printf("in DsDelegate::setEditorData m_preData = %.6f\n",m_preData);
}

void DsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->interpretText();
    double value = doubleSpinBox->value();
    printf("the value is:%.6f\n",value);
    if((value-m_preData)>0.0000001||(value-m_preData)<-0.0000001)
    {
       qDebug()<<"set model data";
       model->setData(index, QVariant(value), Qt::EditRole);
       DsPropertyDisplay::FrameAttr attr_type = static_cast<DsPropertyDisplay::FrameAttr>(index.data(Qt::UserRole).toInt());

       m_view->disconnectDsDataSignal();
       switch(attr_type)
       {
       case DsPropertyDisplay::POSITION_X:
          DsOperator::data()->setCurFrameImagePos(
                          value,
                          m_view->getPosYItemValue());
           break;
        case DsPropertyDisplay::POSITION_Y:
           DsOperator::data()->setCurFrameImagePos(
                                m_view->getPosXItemValue(),
                                value);
            break;
       case DsPropertyDisplay::ROTATE:
           DsOperator::data()->setCurFrameImageAngle(value);
           break;
       case DsPropertyDisplay::SCALE_X:
           DsOperator::data()->setCurFrameImageScale(
                                value,
                                m_view->getScaleYItemValue());
           printf("set the value ScanY = %.6f\n",m_view->getScaleYItemValue());
           break;
       case DsPropertyDisplay::SCALE_Y:
           DsOperator::data()->setCurFrameImageScale(
                                 m_view->getScaleXItemValue(),
                                 value);
           break;
       case DsPropertyDisplay::TEXTURE_X0:
           DsOperator::data()->setCurFrameImageTextureArea(
                               value,
                               m_view->getTextureY0ItemValue(),
                               m_view->getTextureX1ItemValue(),
                               m_view->getTextureY1ItemValue());
           break;
       case DsPropertyDisplay::TEXTURE_Y0:
           DsOperator::data()->setCurFrameImageTextureArea(
                               m_view->getTextureX0ItemValue(),
                               value,
                               m_view->getTextureX1ItemValue(),
                               m_view->getTextureY1ItemValue());
           break;
       case DsPropertyDisplay::TEXTURE_X1:
           DsOperator::data()->setCurFrameImageTextureArea(
                               m_view->getTextureX0ItemValue(),
                               m_view->getTextureY0ItemValue(),
                               value,
                               m_view->getTextureY1ItemValue());
           break;
       case DsPropertyDisplay::TEXTURE_Y1:
           DsOperator::data()->setCurFrameImageTextureArea(
                               m_view->getTextureX0ItemValue(),
                               m_view->getTextureY0ItemValue(),
                               m_view->getTextureX1ItemValue(),
                               value);
           break;
       case DsPropertyDisplay::OFFSET_X:
           DsOperator::data()->setCurFrameImageOffset(
                       value,
                       m_view->getOffetYValue());
           break;
       case DsPropertyDisplay::OFFSET_Y:
           DsOperator::data()->setCurFrameImageOffset(
                       m_view->getOffetXValue(),
                       value);
           break;
       case DsPropertyDisplay::ALPHA:
           DsOperator::data()->setCurFrameImageAlpha(value);
           break;
       case DsPropertyDisplay::FPS:
          // DsOperator::data()->setAnimationFps(value);
           break;
        default:
           break;
       }
        m_view->connectDsDataSignal();
    }
}

void DsDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
    qDebug()<<"in update";
    editor->setGeometry(option.rect);
}

QSize DsDelegate::sizeHint ( const QStyleOptionViewItem & option,
                 const QModelIndex & index ) const
{
    qDebug()<<"in sizeHint";
    QSize size = QItemDelegate::sizeHint(option, index);
    size.setHeight( size.height() + 10 );
    return size;
}

