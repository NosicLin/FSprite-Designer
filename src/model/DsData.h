#ifndef _DS_DATA_H_
#define _DS_DATA_H_
#include <string>
#include <vector>
#include <QImage>
#include <QObject>

#include "DsProject.h"
#include "DsSprite.h"
#include "DsAnimation.h"
#include "DsFrame.h"
#include "DsFrameImage.h"

class DsImage
{

public:
    DsImage(const std::string _name,QImage* _image,int _tex)
    {
        name=_name;
        image=_image;
        texture=_tex;
    }
    std::string getPathRelativeToProject(){return "roject";}

    std::string pathRelativeToProject;
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
        SG_CUR_SPRITE_CHANGE,
        SG_CUR_ANIMATION_CHANGE,
        SG_CUR_FRAME_CHANGE,
        SG_CUR_FRAME_IMAGE_CHANGE,

        SG_PROJECT_PROPERTY_CHANGE,
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
    void setProject(DsProject* proj);
    DsProject* getProject(){return m_curProject;}

    DsSprite* getSprite(int index);
    int getSpriteNu();


    void removeSprite(const std::string& id);
    void renameSprite(const std::string& id,const std::string& target);

    void setCurSprite(const std::string& id);
    DsSprite* getCurSprite();
    DsProject::DsSpriteInfo* getCurSpriteInfo();


	/* animation */
    DsAnimation* getCurAnimation();
    void setCurAnimation(const std::string& anim);
	void dropCurAnimation();
	bool renameAnimation(const std::string& project,const std::string& animation,const std::string& target);

	/* frame */
    DsFrame* getCurFrame();
    int getCurFrameIndex();
    int getFrameNu();
    void setCurFrameIndex(int framenu);
	void dropCurFrame();

	/* frame image */
    DsFrameImage* getCurFrameImage();
    void  setCurFrameImage(const std::string& name);
	void dropCurFrameImage();
    void emitSignal(int type);

    /* save State used for undo/redo */
    void saveState();

signals:
    void signalCurProjectChange();
    void signalCurSpriteChange();
    void signalCurAnimationChange();
    void signalCurFrameChange();
    void signalCurFrameImageChange();

    void signalProjectPropertyChange();
    void signalAnimationPropertyChange();
    void signalFramePropertyChange();
    void signalFrameImagePropertyChange();

private:
    DsProject* m_curProject;
};
#endif /*_DS_DATA_H_*/


















