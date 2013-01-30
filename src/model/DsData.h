#ifndef _DS_DATA_H_
#define _DS_DATA_H_
#include <string>
#include <vector>
#include <QImage>
#include <QObject>

#include "DsProject.h"
class DsSprite;
class DsAnimation;
class DsFrame;
class DsFrameImage;


class DsImage
{

public:
    DsImage(const std::string _name,QImage* _image,int _tex)
    {
        name=_name;
        image=_image;
        texture=_tex;
    }

    std::string name;
    QImage* image;
    int texture;
};

class DsData:public QObject
{
    Q_OBJECT

public:
    enum
    {
        SG_CUR_PROJECT_CHANGE,
        SG_CUR_ANIMATION_CHANGE,
        SG_CUR_FRAME_CHANGE,
        SG_CUR_FRAME_IMAGE_CHANGE,

        SG_PROJECT_PROPERTY_CHANGE,
        SG_SPRITE_PROPERTY_CHANGE,
        SG_ANIMATION_PROPERTY_CHANGE,
        SG_FRAME_PROPERTY_CHANGE,
        SG_FRAME_IMAGE_PROPERTY_CHANGE
    };

public:
    static DsData* shareData();
public:
    DsData();
    ~DsData();
public:
    DsProject* getCurProject();
    void setCurProject(DsProject* proj);
    DsSprite* getCurSprite();

    DsAnimation* getCurAnimation();
    void setCurAnimation(const std::string& anim);
	void dropCurAnimation();

    DsFrame* getCurFrame();
    int getCurFrameIndex();
    int getFrameNu();
    void setCurFrameIndex(int framenu);
	void dropCurFrame();

    DsFrameImage* getCurFrameImage();
    void  setCurFrameImage(const std::string& name);
	void dropCurFrameImage();

    void emitSignal(int type);

signals:
    void signalCurProjectChange();
    void signalCurAnimationChange();
    void signalCurFrameChange();
    void signalCurFrameImageChange();

    void signalProjectPropertyChange();
    void signalSpritePropertyChange();
    void signalAnimationPropertyChange();
    void signalFramePropertyChange();
    void signalFrameImagePropertyChange();

private:
    DsProject* m_curProject;
};
#endif /*_DS_DATA_H_*/


















