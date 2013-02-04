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


DsProject* DsData::getCurProject(){
    return m_curProject;
}


void DsData::setCurProject(const std::string& name)
{
	for(int i=0;i<m_projects.size();i++)
	{
		if(m_projects[i]->getName()==name)
		{
            m_curProject=m_projects[i];
			return ;
		}
	}
	assert(0); /*never reached here */
}
DsProject* DsData::getProject(const std::string& name)
{
	for(int i=0;i<m_projects.size();i++)
	{
		if(m_projects[i]->getName()==name)
		{
			return m_projects[i];
		}
	}
	assert(0); /*never reached here */
	return NULL;
}
DsProject* DsData::getProject(int index)
{
	assert(index>=0&&index<m_projects.size());
    return m_projects[index];
}

void DsData::addProject(DsProject* project)
{
	m_projects.push_back(project);
}

void DsData::removeProject(const std::string& name)
{
	std::vector<DsProject*>::iterator iter;
	for(iter=m_projects.begin();iter!=m_projects.end();++iter)
	{
		if((*iter)->getName()==name)
		{
			if((*iter)==m_curProject)
			{
				m_curProject=NULL;
			}
			m_projects.erase(iter);
			return ;
		}
	}
	assert(0); /* never reached here */
}

int DsData::getProjectNu()
{
	return m_projects.size();
}




void DsData::renameProject(const std::string& name,const std::string& target)
{
	std::vector<DsProject*>::iterator iter;
	for(iter=m_projects.begin();iter!=m_projects.end();++iter)
	{
		if((*iter)->getName()==name)
		{
			(*iter)->setName(target);
			return ;
		}
    }
    assert(0);/* never reached here */

}




void DsData::emitSignal(int type)
{

	switch(type)
	{
		case SG_DATA_PROPERTY_CHANGE:
			emit signalDataPropertyChange();
			break;

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
		return m_curProject->getCurAnimation();
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





