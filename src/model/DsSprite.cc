#include <assert.h>
#include "DsSprite.h"
#include "DsAnimation.h"

DsSprite::DsSprite(const std::string& name)
{
	m_name=name;
}

void DsSprite::addAnimation(DsAnimation* anim)
{
    m_animations.push_back(anim);
}

void DsSprite::removeAnimation(const std::string& name)
{
	Iterator iter=m_animations.begin();
	for(;iter!=m_animations.end();++iter)
	{
        if((*iter)->getName()==name)
		{
			m_animations.erase(iter);
			return;
		}
	}
	assert(0); /*never reach here*/
}

DsAnimation* DsSprite::getAnimation(const std::string& name)
{
	Iterator iter=m_animations.begin();
	for(;iter!=m_animations.end();++iter)
	{
        if((*iter)->getName()==name)
		{
			return *iter;
		}
	}
    assert(0); /*never reach here*/
    return NULL;
}







