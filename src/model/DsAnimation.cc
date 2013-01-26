#include <assert.h>


#include "DsAnimation.h"
#include "DsFrame.h"
int DsAnimation::m_defaulFps=10;

DsAnimation::DsAnimation(const std::string& name)
{
	m_name=name;
	m_fps=m_defaulFps;
}

DsAnimation::~DsAnimation()
{
	Iterator iter;
	for(iter=m_frames.begin();iter!=m_frames.end();++iter)
	{
		delete *iter;
	}
	m_frames.clear();
}

void DsAnimation::pushFrame(DsFrame* anim)
{
    m_frames.push_back(anim);
}


DsFrame* DsAnimation::getFrame(int index)
{
	assert(index<m_frames.size());
	return m_frames[index];
}

void DsAnimation::removeFrame(int index)
{
	assert(index<m_frames.size());
	DsFrame* frame=m_frames[index];
	delete frame;
//	m_frames.erase(index);
}

void DsAnimation::insertFrame(DsFrame* anim,int index)
{
    //m_frames.insert(index,anim);
}
void DsAnimation::swapFrame(int l,int r)
{
	DsFrame* temp=m_frames[l];
	m_frames[l]=m_frames[r];
	m_frames[r]=temp;
}
















