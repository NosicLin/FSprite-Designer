#include <assert.h>
#include "DsFrame.h"
#include "DsFrameImage.h"

DsFrame::DsFrame()
{
	m_name="Frame";
}
DsFrame::DsFrame(const std::string& name)
{
	m_name=name;
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

void DsFrame::pushFrameImage(DsFrameImage* image)
{
	m_images.push_back(image);
}
















