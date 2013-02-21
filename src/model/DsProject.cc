#include <assert.h>
#include "DsProject.h"
#include "DsSprite.h"
#include "DsAnimation.h"
#include "DsFrame.h"
#include "DsFrameImage.h"

void DsProject::DsSpriteInfo::setCurAnimationByID(const std::string& id)
{
    m_curAnimation=m_sprite->getAnimationByID(id);
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
    m_curFrameIndex=frame;
    m_curFrameImage=NULL;
}

void DsProject::DsSpriteInfo::setCurFrameImageByID(const std::string& id)
{
    if(m_curFrameIndex==-1)
    {
        return;
    }

    DsFrame* frame=m_curAnimation->getFrame(m_curFrameIndex);
    assert(frame);
    assert(frame->getType()==DsFrame::FRAME_KEY);
    m_curFrameImage=((DsKeyFrame*)frame)->getFrameImageByID(id);
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






DsSprite* DsProject::getCurSprite()
{
	if(m_curSprite)
	{
		return m_curSprite->m_sprite;
	}
	return NULL;
}

void DsProject::setCurSpriteByID(const std::string& id)
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

void DsProject::setCurAnimationByID(const std::string& id)
{
	if(m_curSprite)
	{
		m_curSprite->setCurAnimationByID(id);
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
		m_curSprite->getCurFrame();
    }
    return NULL;
}

int DsProject::getCurFrameIndex()
{
	if(m_curSprite)
	{
		m_curSprite->getCurFrameIndex();
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

void DsProject::setCurFrameImageByID(const std::string& id)
{
	if(m_curSprite)
	{
		return m_curSprite->setCurFrameImageByID(id);
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

DsSprite* DsProject::getSpriteByID(const std::string& id)
{
	for(int i=0;i<m_sprites.size();i++)
	{
        if(m_sprites[i]->m_sprite->getID()==id)
		{
			return m_sprites[i]->m_sprite;
		}
	}
	assert(0); /*never reach here */
	return NULL;
}



























































































