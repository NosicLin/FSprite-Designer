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
