#include <assert.h>


#include "DsAnimation.h"
#include "DsFrame.h"
int DsAnimation::m_defaulFps=10;

DsAnimation::DsAnimation(const std::string& name)
{
	m_name=name;
	m_fps=m_defaulFps;

	DsFrame* frame=new DsFrame();
	frame->setFrameId(0);
	m_keyFrames.push_back(frame);

}


DsAnimation::~DsAnimation()
{
	Iterator iter;
    for(iter=m_keyFrames.begin();iter!=m_keyFrames.end();++iter)
	{
		delete *iter;
	}
    m_keyFrames.clear();
}

DsFrame* DsAnimation::getFrame(int index)
{
	int keyid=toKeyFramePos(index);
	return m_keyFrames[keyid];
}

void DsAnimation::insertFrame(DsFrame* frame)
{
	int frameid=frame->getFrameId();
    int keyid=toKeyFramePos(frameid);
    if(m_keyFrames[keyid]->getFrameId()==frameid)
    {
        assert(m_keyFrames[keyid]!=frame);

        delete m_keyFrames[keyid];
        m_keyFrames[keyid]=frame;
    }
    else
    {
        m_keyFrames.insert(m_keyFrames.begin()+keyid+1,frame);
    }
}

void DsAnimation::removeKeyFrame(int index)
{
	int keyid=toKeyFramePos(index);
	assert(m_keyFrames[keyid]->getFrameId()==index);
	m_keyFrames.erase(m_keyFrames.begin()+keyid);
}
void DsAnimation::insertKeyFrame(int index)
{
	DsFrame* orign=getFrame(index);
	DsFrame* now=orign->clone();
	insertFrame(now);
}


int DsAnimation::toKeyFramePos(int index)
{
    assert(m_keyFrames.size()>=1);
	for(int i=0;i<m_keyFrames.size();i++)
	{
		int frameid=m_keyFrames[i]->getFrameId();
		if(frameid==index)
		{
			return i;
		}
		if(frameid>index)
		{
			assert(i>=1);
			return i-1;
		}
	}
    return m_keyFrames.size()-1;
}

int DsAnimation::getFrameNu()
{
    return m_keyFrames[m_keyFrames.size()-1]->getFrameId()+1;
}










