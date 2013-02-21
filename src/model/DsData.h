#ifndef _DS_DATA_H_
#define _DS_DATA_H_
#include <string>
#include <vector>
#include <QImage>
#include <QObject>

class DsProject;
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


    void addSprite(DsProject* project);
    void removeSpriteByID(const std::string& id);
    void renameSpriteByID(const std::string& id,const std::string& target);

    void setCurSpriteByID(const std::string& id);
    DsSprite* getCurSprite();


	/* animation */
    DsAnimation* getCurAnimation();
    void setCurAnimationByID(const std::string& anim);
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
    void  setCurFrameImageByID(const std::string& name);
	void dropCurFrameImage();
    void emitSignal(int type);

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


















