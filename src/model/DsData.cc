#include "DsData.h"
#include "assert.h"

DsData* s_shareData=NULL;

DsData* DsData::shareData()
{
	if(s_shareData==NULL)
	{
		s_shareData=new DsData;
	}
	return s_shareData;
}


DsData::DsData()
{
	m_curProject=NULL;
}

void DsData::emitSignal(int type)
{

	switch(type)
	{
		case SG_CUR_PROJECT_CHANGE:
			emit signalCurProjectChange();
			break;
		case SG_CUR_ANIMATION_CHANGE:
			emit signalCurAnimationChange();
			break;
		case SG_CUR_FRAME_CHANGE:
			emit signalCurFrameChange();
			break;
		case SG_CUR_FRAME_IMAGE_CHANGE:
			emit signalCurFrameImageChange();
			break;


		case SG_PROJECT_PROPERTY_CHANGE:
			emit signalProjectPropertyChange();
			break;

		case SG_SPRITE_PROPERTY_CHANGE:
			emit signalSpritePropertyChange();
			break;

		case SG_ANIMATION_PROPERTY_CHANGE:
			emit signalAnimationPropertyChange();
			break;

		case SG_FRAME_PROPERTY_CHANGE:
			emit signalFramePropertyChange();
			break;
		case SG_FRAME_IMAGE_PROPERTY_CHANGE:
			emit signalFrameImagePropertyChange();
			break;

		default:
			assert(0);
	}
}


DsSprite* DsData::getCurSprite()
{
	return m_curProject->getSprite();
}



DsAnimation* DsData::getCurAnimation()
{
	if(m_curProject)
	{
		return m_curProject->getCurAniamtion();
	}
	return NULL;
}
void DsData::setCurAnimation(const std::string& anim)
{
	if(m_curProject)
	{
		m_curProject->setCurAnimation(anim);
	}
}
void DsData::dropCurAnimation()
{
	if(m_curProject)
	{
		m_curProject->dropCurAnimation();
	}
}

DsFrame* DsData::getCurFrame()
{
	if(m_curProject)
	{
		return m_curProject->getCurFrame();
	}
	return NULL;
}

void DsData::setCurFrame(int framenu)
{
	if(m_curProject)
	{
		return m_curProject->setCurFrame(framenu);
	}
}
void DsData::dropCurFrame()
{
	if(m_curProject)
	{
		m_curProject->dropCurFrame();
	}
}

DsFrameImage* DsData::getCurFrameImage()
{
	if(m_curProject)
	{
		return m_curProject->getCurFrameImage();
	}
	return NULL;
}
void  DsData::setCurFrameImage(const std::string& name)
{
	if(m_curProject)
	{
		m_curProject->setCurFrameImage(name);
	}
}
void DsData::dropCurFrameImage()
{
	if(m_curProject)
	{
		m_curProject->dropCurFrameImage();
	}
}





