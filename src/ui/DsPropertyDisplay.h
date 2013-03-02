#ifndef _DS_PROPERTY_DISPLAY_H_
#define _DS_PROPERTY_DISPLAY_H_ 

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSlider>
class DsPropertyDisplay:public QWidget
{
    Q_OBJECT
public:
		DsPropertyDisplay(QWidget* parent);


private slots:
        void slotSetDoubleSpinBoxValue(int value);
        void slotSetSliderValue(double value);

        //deal with FrameImage property change
        void slotFrameImagePropertyChange();

        //set FrameImage property
        void slotSetPositon();
        void slotSetAngle(double value);
        void slotSetScale();

        void slotSetTextureArea();

        void slotSetOffset();

        void slotSetAlpha(double value);

private:
        void createLayout();
        void connectDsDataSignal();
        void disconnectDsDataSignal();
        void connectAllSpinBox();
        void disconnectAllSpinBox();
signals:


private:
    //position
    QLabel* m_posLabel;
    QLabel* m_posXLabel;
    QLabel* m_posYLabel;
    QDoubleSpinBox* m_posXDoubleSpinbox;
    QDoubleSpinBox* m_posYDoubleSpinbox;

    //angle
    QLabel* m_angleLabel;
    QLabel* m_angLabel;
    QDoubleSpinBox* m_angleSpinDoubleBox;

    //scale
    QLabel* m_scaleLabel;
    QLabel* m_scaleXLabel;
    QLabel* m_scaleYLabel;
    QDoubleSpinBox*  m_scaleXDoubleSpinBox;
    QDoubleSpinBox*  m_scaleYDoubleSpinBox;

    //texture
    QLabel* m_textureLabel;
    QLabel* m_textureX0Label;
    QLabel* m_textureY0Label;
    QLabel* m_textureX1Label;
    QLabel* m_textureY1Label;
    QDoubleSpinBox*  m_textureX0DoubleSpinBox;
    QDoubleSpinBox*  m_textureY0DoubleSpinBox;
    QDoubleSpinBox*  m_textureX1DoubleSpinBox;
    QDoubleSpinBox*  m_textureY1DoubleSpinBox;

    //offset
    QLabel* m_offsetLabel;
    QLabel* m_offsetXLabel;
    QLabel* m_offsetYLabel;
    QDoubleSpinBox* m_offsetXDoubleSpinbox;
    QDoubleSpinBox* m_offsetYDoubleSpinbox;

    //alpha
    QLabel* m_alphaLabel;
    QLabel* m_alLabel;
    QDoubleSpinBox* m_alphaDoubleSpinBox;
    QSlider* m_alphaSlider;

};
#endif /*_DS_EDIT_VIEW_H_*/






