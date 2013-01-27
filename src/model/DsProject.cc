#include <assert.h>

#include "DsProject.h"
#include "DsAnimation.h"
#include "DsSprite.h"



void DsProject::setCurAnimation(const std::string& name)
{
	m_curAnimation=m_sprite->getAnimation(name);
	assert(m_curAnimation);

	if(m_curAnimation->getFrameNu()>0)
	{
		m_curFrame=m_curAnimation->getFrame(0);
	}
	else 
	{
		m_curFrame=NULL;
	}
	m_curFrameImage=NULL;
}

void DsProject::setCurFrame(int frame)
{
	if(!m_curAnimation)
	{
		return;
	}
	m_curFrame=m_curAnimation->getFrame(frame);
	m_curFrameImage=NULL;
}

void DsProject::setCurFrameImage(const std::string& name)
{
	if(!m_curFrame)
	{
		return;
	}
	m_curFrameImage=m_curFrame->getFrameImage(name);
	assert(m_curFrameImage);
}


void DsProject::dropCurAnimation()
{
	m_curAnimation=NULL;
	m_curFrame=NULL;
	m_curFrameImage=NULL;
}
void DsProject::dropCurFrame()
{
	m_curFrame=NULL;
	m_curFrameImage=NULL;
}
void DsProject::dropCurFrameImage()
{
	m_curFrameImage=NULL;
}


