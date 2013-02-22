#include <stdio.h>
#include <assert.h>

#include "util/DsUtil.h"
#include "DsSprite.h"
#include "DsAnimation.h"
#include "DsSprite.h"

DsSprite::DsSprite()
{
    m_id=DsUtil::uniqueStringID();
}
DsSprite::DsSprite(const std::string& name)
{
    m_name=name;
	m_id=DsUtil::uniqueStringID();
}

void DsSprite::addAnimation(DsAnimation* anim)
{
    m_animations.push_back(anim);
}


void DsSprite::removeAnimation(const std::string& id)
{
	Iterator iter=m_animations.begin();
	for(;iter!=m_animations.end();++iter)
	{
        if((*iter)->getID()==id)
		{
			m_animations.erase(iter);
			return;
		}
	}
	assert(0); /*never reach here*/
}

DsAnimation* DsSprite::getAnimation(const std::string& id)
{
	Iterator iter=m_animations.begin();
	for(;iter!=m_animations.end();++iter)
	{
        if((*iter)->getID()==id)
		{
			return *iter;
		}
	}
    assert(0); /*never reach here*/
    return NULL;
}

bool DsSprite::hasAnimationWithName(const std::string& name)
{
    Iterator iter=m_animations.begin();
    for(;iter!=m_animations.end();++iter)
    {
        if((*iter)->getName()==name)
        {
            return true;
        }
    }
    return false;
}

DsAnimation* DsSprite::getAnimation(int index)
{
    assert(index>=0&&index<=m_animations.size());
	return m_animations[index];
}









