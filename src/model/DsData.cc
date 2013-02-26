#include "DsData.h"
#include "assert.h"
#include "ui/DsEditView.h"
#include "util/DsDebug.h"

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

DsData::~DsData()
{
}

void DsData::setProject(DsProject* proj)
{
    if(m_curProject)
    {
        delete m_curProject;
    }
    m_curProject=proj;
}


DsSprite* DsData::getCurSprite()
{
	if(m_curProject)
	{
		return m_curProject->getCurSprite();
	}
	return NULL;
}
DsProject::DsSpriteInfo* DsData::getCurSpriteInfo()
{
    if(m_curProject)
    {
        return m_curProject->getCurSpriteInfo();
    }
}

void DsData::setCurSprite(const std::string& id)
{
    m_curProject->setCurSprite(id);
}



void DsData::emitSignal(int type)
{

	switch(type)
	{
		case SG_CUR_PROJECT_CHANGE:
			emit signalCurProjectChange();
			break;
        case SG_CUR_SPRITE_CHANGE:
            emit signalCurSpriteChange();
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

DsAnimation* DsData::getCurAnimation()
{
	if(m_curProject)
	{
		return m_curProject->getCurAnimation();
	}
	return NULL;
}

void DsData::setCurAnimation(const std::string& id)
{
	if(m_curProject)
	{
        m_curProject->setCurAnimation(id);
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



int DsData::getCurFrameIndex()
{
	if(m_curProject)
    {
		return m_curProject->getCurFrameIndex();
	}
	return -1;
}



void DsData::setCurFrameIndex(int framenu)
{
	if(m_curProject)
	{
		return m_curProject->setCurFrameIndex(framenu);
	}
}


int DsData::getFrameNu()
{
	if(m_curProject)
	{
		DsAnimation* anim=m_curProject->getCurAnimation();
		if(anim)
		{
			return anim->getFrameNu();
		}

	}
	return 0;
}




void DsData::dropCurFrame()
{
	if(m_curProject)
	{
		m_curProject->dropCurFrameIndex();
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

void  DsData::setCurFrameImage(const std::string& id)
{
	if(m_curProject)
	{
        m_curProject->setCurFrameImage(id);
	}
}

void DsData::dropCurFrameImage()
{
	if(m_curProject)
	{
		m_curProject->dropCurFrameImage();
	}
}





