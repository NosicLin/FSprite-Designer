#include <assert.h>
#include "DsFrame.h"
#include "DsFrameImage.h"


DsTweenFrame::DsTweenFrame(DsKeyFrame* from,DsKeyFrame* to,int id)
	:DsFrame(id)
{
	m_from=from;
	m_to=to;
}

void DsTweenFrame::setFromKeyFrame(DsKeyFrame* from)
{
	m_from=from;
}
void DsTweenFrame::setToKeyFrame(DsKeyFrame* to)
{
	m_to=to;
}

DsKeyFrame* DsTweenFrame::slerpToKeyFrame(int index)
{
    return NULL;
}



DsFrameImage* DsKeyFrame::getFrameImage(const std::string& name)
{
	Iterator iter=m_images.begin();
	for(;iter!=m_images.end();++iter)
	{
        if((*iter)->getName()==name)
		{
			return (*iter);
		}
	}
	assert(0);
	return  NULL;
}


DsKeyFrame::DsKeyFrame(int id)
	:DsFrame(id)
{
}




DsFrameImage* DsKeyFrame::getFrameImage(int index)
{
	assert(index<m_images.size());
    return m_images[index];
}


void DsKeyFrame::pushFrameImage(DsFrameImage* image)
{
	m_images.push_back(image);
}


DsKeyFrame* DsKeyFrame::clone()
{
    DsKeyFrame* ret=new DsKeyFrame(0);

	Iterator iter=m_images.begin();
	for(;iter!=m_images.end();++iter)
	{
		DsFrameImage* frameImage=(*iter)->clone();
        ret->m_images.push_back(frameImage);
	}
	return ret;
}










































