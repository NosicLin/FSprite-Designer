#include <assert.h>

#include "util/DsDebug.h"
#include "DsProject.h"
#include "DsSprite.h"
#include "DsAnimation.h"
#include "DsFrame.h"
#include "DsFrameImage.h"


DsProject::DsSpriteInfo::DsSpriteInfo(DsSprite* sprite)
{
    m_curFrameIndex=-1;
    m_curAnimation=0;
    m_curFrameImage=NULL;
    m_sprite=sprite;

	m_copyFrameImage=NULL;
	m_copyFrame=NULL;
}

DsProject::DsSpriteInfo::~DsSpriteInfo()
{
    delete m_sprite;
}

void DsProject::DsSpriteInfo::setCurAnimation(const std::string& id)
{
    m_curAnimation=m_sprite->getAnimation(id);
    assert(m_curAnimation);

    if(m_curAnimation->getFrameNu()>0)
    {
        m_curFrameIndex=0;
    }
    else
    {
        m_curFrameIndex=-1;
    }
    m_curFrameImage=NULL;
}


void DsProject::DsSpriteInfo::setCurFrameIndex(int frame)
{
    if(!m_curAnimation)
    {
        return;
    }
    DsDebug<<"m_curframeIndex:"<<m_curFrameIndex<<endl;
    m_curFrameIndex=frame;
    m_curFrameImage=NULL;
}

void DsProject::DsSpriteInfo::setCurFrameImage(const std::string& id)
{
    if(m_curFrameIndex==-1)
    {
        return;
    }
    DsFrame* frame=m_curAnimation->getFrame(m_curFrameIndex);

    assert(frame);
    assert(frame->getType()==DsFrame::FRAME_KEY);
    m_curFrameImage=((DsKeyFrame*)frame)->getFrameImage(id);
    assert(m_curFrameImage);
}


void DsProject::DsSpriteInfo::dropCurAnimation()
{
    m_curAnimation=NULL;
    m_curFrameIndex=-1;
    m_curFrameImage=NULL;
}



void DsProject::DsSpriteInfo::dropCurFrameIndex()
{
    m_curFrameIndex=-1;
    m_curFrameImage=NULL;
}

void DsProject::DsSpriteInfo::dropCurFrameImage()
{
    m_curFrameImage=NULL;
}

DsFrame* DsProject::DsSpriteInfo::getCurFrame()
{
    if(!m_curAnimation)
    {
        return NULL;
    }
    if(m_curFrameIndex==-1)
    {
        return NULL;
    }
    return m_curAnimation->getFrame(m_curFrameIndex);
}

DsAnimation* DsProject::DsSpriteInfo::getCurAnimation()
{
	return m_curAnimation;
}

DsFrameImage* DsProject::DsSpriteInfo::getCurFrameImage()
{
	return m_curFrameImage;
}

int DsProject::DsSpriteInfo::getCurFrameIndex()
{
    return m_curFrameIndex;
}

void DsProject::DsSpriteInfo::setCopyFrameImage(DsFrameImage* image)
{
    if(m_copyFrameImage)
    {
        delete m_copyFrameImage;
    }
    m_copyFrameImage=image;
}




DsProject::DsProject()
{
    m_curSprite=NULL;
}

DsProject::~DsProject()
{
    for(int i=0;i<m_sprites.size();i++)
    {
        delete m_sprites[i];
    }
    m_sprites.clear();
}

DsSprite* DsProject::getCurSprite()
{
    if(m_curSprite)
    {
        return m_curSprite->m_sprite;
    }
    return NULL;
}

void DsProject::setCurSprite(const std::string& id)
{
    for(int i=0;i<m_sprites.size();i++)
    {
        if(m_sprites[i]->m_sprite->getID()==id)
        {
            m_curSprite=m_sprites[i];
            return;
        }
    }
    assert(0); /*never reach here */
}

DsAnimation* DsProject::getCurAnimation()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurAnimation();
    }
    return NULL;
}

void DsProject::setCurAnimation(const std::string& id)
{
    if(m_curSprite)
    {
        m_curSprite->setCurAnimation(id);
    }
}
void DsProject::dropCurAnimation()
{
    if(m_curSprite)
    {
        m_curSprite->dropCurAnimation();
    }
}

DsFrame* DsProject::getCurFrame()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurFrame();
    }
    return NULL;
}

int DsProject::getCurFrameIndex()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurFrameIndex();
    }
    return -1;
}
void DsProject::setCurFrameIndex(int index)
{
    if(m_curSprite)
    {
        m_curSprite->setCurFrameIndex(index);
    }
}
void DsProject::dropCurFrameIndex()
{
    if(m_curSprite)
    {
        m_curSprite->dropCurFrameIndex();
    }
}


DsFrameImage* DsProject::getCurFrameImage()
{
    if(m_curSprite)
    {
        return m_curSprite->getCurFrameImage();
    }
    return NULL;
}

void DsProject::setCurFrameImage(const std::string& id)
{
    if(m_curSprite)
    {
        return m_curSprite->setCurFrameImage(id);
    }
}

void DsProject::dropCurFrameImage()
{
    if(m_curSprite)
    {
        m_curSprite->dropCurFrameImage();
    }
}


DsSprite* DsProject::getSprite(int index)
{
    assert(index>=0&&index<m_sprites.size());
    return m_sprites[index]->m_sprite;
}

DsSprite* DsProject::getSprite(const std::string& id)
{
    for(unsigned int i=0;i<m_sprites.size();i++)
    {
        if(m_sprites[i]->m_sprite->getID()==id)
        {
            return m_sprites[i]->m_sprite;
        }
    }
    assert(0); /*never reach here */
    return NULL;
}


void DsProject::addSprite(DsSprite* sprite)
{
    m_sprites.push_back(new DsSpriteInfo(sprite));
}

bool DsProject::hasSpriteWithName(const std::string& name)
{
    for(unsigned int i=0;i<m_sprites.size();i++)
    {
        if(m_sprites[i]->m_sprite->getName()==name)
        {
            return true;
        }
    }
    return false;
}


























































































