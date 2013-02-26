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
signals:


private:
    //position
    QLabel* posLabel;
    QLabel* posXLabel;
    QLabel* posYLabel;
    QDoubleSpinBox* posXDoubleSpinbox;
    QDoubleSpinBox* posYDoubleSpinbox;

    //angle
    QLabel* angleLabel;
    QLabel* angLabel;
    QDoubleSpinBox* angleSpinDoubleBox;

    //scale
    QLabel* scaleLabel;
    QLabel* scaleXLabel;
    QLabel* scaleYLabel;
    QDoubleSpinBox*  scaleXDoubleSpinBox;
    QDoubleSpinBox*  scaleYDoubleSpinBox;

    //texture
    QLabel* textureLabel;
    QLabel* textureX0Label;
    QLabel* textureY0Label;
    QLabel* textureX1Label;
    QLabel* textureY1Label;
    QDoubleSpinBox*  textureX0DoubleSpinBox;
    QDoubleSpinBox*  textureY0DoubleSpinBox;
    QDoubleSpinBox*  textureX1DoubleSpinBox;
    QDoubleSpinBox*  textureY1DoubleSpinBox;

    //offset
    QLabel* offsetLabel;
    QLabel* offsetXLabel;
    QLabel* offsetYLabel;
    QDoubleSpinBox* offsetXDoubleSpinbox;
    QDoubleSpinBox* offsetYDoubleSpinbox;

    //alpha
    QLabel* alphaLabel;
    QLabel* alLabel;
    QDoubleSpinBox* alphaDoubleSpinBox;
    QSlider* alphaSlider;


};
#endif /*_DS_EDIT_VIEW_H_*/






