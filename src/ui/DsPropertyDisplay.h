#ifndef _DS_PROPERTY_DISPLAY_H_
#define _DS_PROPERTY_DISPLAY_H_ 

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QTreeview>

#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QAbstractItemDelegate>
#include "DsDelegate.h"

class DsPropertyDisplay:public QWidget
{
    Q_OBJECT
public:
    enum FrameAttr
    {
        POSITION_X = 1,
        POSITION_Y,
        ROTATE,
        SCALE_X,
        SCALE_Y,
        TEXTURE_X0,
        TEXTURE_Y0,
        TEXTURE_X1,
        TEXTURE_Y1,
        OFFSET_X,
        OFFSET_Y,
        ALPHA,
        FPS
    };

public:
		DsPropertyDisplay(QWidget* parent);
private slots:
        void slotFrameImagePropertyChange();

public:
        void initProperty();
        void connectDsDataSignal();
        void disconnectDsDataSignal();
public:
        double getPosXItemValue()
        {
            return m_posXValueItem->data(Qt::EditRole).toDouble();
        }

        double getPosYItemValue()
        {
            return m_posYValueItem->data(Qt::EditRole).toDouble();
        }
        double getAngleItemValue()
        {
            return m_angleValueItem->data(Qt::EditRole).toDouble();
        }
        double getScaleXItemValue()
        {
            return m_scaleXValueItem->data(Qt::EditRole).toDouble();
        }
        double getScaleYItemValue()
        {
            printf("getScaleYItemValue value = \n");
            return m_scaleYValueItem->data(Qt::EditRole).toDouble();
        }
        double getTextureX0ItemValue()
        {
            return m_textureX0ValueItem->data(Qt::EditRole).toDouble();
        }
        double getTextureY0ItemValue()
        {

            return m_textureY0ValueItem->data(Qt::EditRole).toDouble();
        }
        double getTextureX1ItemValue()
        {
            return m_textureX1ValueItem->data(Qt::EditRole).toDouble();
        }
        double getTextureY1ItemValue()
        {
            return m_textureY1ValueItem->data(Qt::EditRole).toDouble();
        }
        double getOffetXValue()
        {
            return m_offsetXValueItem->data(Qt::EditRole).toDouble();
        }
        double getOffetYValue()
        {
            return m_offsetYValueItem->data(Qt::EditRole).toDouble();
        }
        double getAlphaItemValue()
        {
            return m_alphaValueItem->data(Qt::EditRole).toDouble();
        }
private:
    QStandardItem* m_posItem;
    QStandardItem* m_posEmptyItem;
    QStandardItem* m_posXItem;
    QStandardItem* m_posYItem;
    QStandardItem* m_posXValueItem;
    QStandardItem* m_posYValueItem;

    //rotate
    QStandardItem* m_rotateItem;
    QStandardItem* m_rotateEmptyItem;
    QStandardItem* m_angleItem;
    QStandardItem* m_angleValueItem;

    //scale
    QStandardItem* m_scaleItem;
    QStandardItem* m_scaleEmptyItem;
    QStandardItem* m_scaleXItem;
    QStandardItem* m_scaleYItem;
    QStandardItem*  m_scaleXValueItem;
    QStandardItem*  m_scaleYValueItem;

    //texture
    QStandardItem* m_textureItem;
    QStandardItem* m_textureEmptyItem;
    QStandardItem* m_textureX0Item;
    QStandardItem* m_textureY0Item;
    QStandardItem* m_textureX1Item;
    QStandardItem* m_textureY1Item;
    QStandardItem* m_textureX0ValueItem;
    QStandardItem* m_textureY0ValueItem;
    QStandardItem* m_textureX1ValueItem;
    QStandardItem* m_textureY1ValueItem;

    //offset
    QStandardItem* m_offsetItem;
    QStandardItem* m_offsetEmptyItem;
    QStandardItem* m_offsetXItem;
    QStandardItem* m_offsetYItem;
    QStandardItem* m_offsetXValueItem;
    QStandardItem* m_offsetYValueItem;

    //alpha
    QStandardItem* m_transItem;
    QStandardItem* m_transEmptyItem;
    QStandardItem* m_alphaItem;
    QStandardItem* m_alphaValueItem;

    //fps
    QStandardItem* m_fpsItem;
    QStandardItem* m_fpsValueItem;


    QStandardItemModel* m_model;
    DsDelegate* m_delegate;
    QTreeView* m_view;
};
#endif /*_DS_EDIT_VIEW_H_*/






