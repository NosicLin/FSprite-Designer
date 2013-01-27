#ifndef _DS_DATA_H_
#define _DS_DATA_H_
#include <string>
#include <vector>
#include <QImage>

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

class DsData
{
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
    DsProject* getCurProject(){return m_curProject;}
    void setCurProject(DsProject* proj){m_curProject=proj;}

    DsSprite* getCurSprite()
    {
        return m_curProject->getSprite();
    }

    DsAnimation* getCurAnimation()
    {
        if(m_curProject)
        {
            return m_curProject->getCurAniamtion();
        }
        return NULL;
    }
    void setCurAnimation(const std::string& anim)
    {
        if(m_curProject)
        {
            m_curProject->setCurAnimation(anim);
        }
    }

    DsFrame* getCurFrame()
    {
        if(m_curProject)
        {
            return m_curProject->getCurFrame();
        }
        return NULL;
    }

    void setCurFrame(int framenu)
    {
        if(m_curProject)
        {
            return m_curProject->setCurFrame(framenu);
        }
    }

    DsFrameImage* getCurFrameImage()
    {
        if(m_curProject)
        {
            return m_curProject->getCurFrameImage();
        }
        return NULL;
    }
    void  setCurFrameImage(const std::string& name)
    {
        if(m_curProject)
        {
            m_curProject->setCurFrameImage(name);
        }
    }

    void emitSignal(int type);

signals:
    void signalCurProjectChange(){}
    void signalCurAnimationChange(){}
    void signalCurFrameChange(){}
    void signalCurFrameImageChange(){}

    void signalProjectPropertyChange(){}
    void signalSpritePropertyChange(){}
    void signalAnimationPropertyChange(){}
    void signalFramePropertyChange(){}
    void signalFrameImagePropertyChange(){}

private:
    DsProject* m_curProject;
};
#endif /*_DS_DATA_H_*/

















