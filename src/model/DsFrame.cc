#include <assert.h>
#include "DsFrame.h"
#include "DsFrameImage.h"

DsFrame::DsFrame()
{
	m_name="Frame";
	m_frameId=0;
}
DsFrame::DsFrame(int id)
{
    m_frameId=id;
    m_name="Frame";
}


DsFrame::~DsFrame()
{
}




DsFrameImage* DsFrame::getFrameImage(const std::string& name)
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



DsFrameImage* DsFrame::getFrameImage(int index)
{
	assert(index<m_images.size());
    return m_images[index];
}


void DsFrame::pushFrameImage(DsFrameImage* image)
{
	m_images.push_back(image);
}


DsFrame* DsFrame::clone()
{
	DsFrame* ret=new DsFrame;

	Iterator iter=m_images.begin();
	for(;iter!=m_images.end();++iter)
	{
		DsFrameImage* frameImage=(*iter)->clone();
        ret->m_images.push_back(frameImage);
	}
	return ret;
}










































