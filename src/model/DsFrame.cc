#include <assert.h>
#include "DsFrame.h"
#include "DsFrameImage.h"
#include "util/DsDebug.h"


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
	DsKeyFrame* ret=new DsKeyFrame(index);
	int begin_id=m_from->getFrameId();
    int end_id=m_to->getFrameId();
    float t= 1-(((float)(index-begin_id))/((float)(end_id-begin_id)));


	int image_nu=m_from->getFrameImageNu();

	if(image_nu>m_to->getFrameImageNu())
	{
		image_nu=m_to->getFrameImageNu();
	}

	for(int i=0;i<image_nu;i++)
	{
		DsFrameImage* from=m_from->getFrameImage(i);
		DsFrameImage* to=m_to->getFrameImage(i);

		DsFrameImage* slerp=from->clone();
		if(from->getImage()==to->getImage())
        {
			float x=from->getPosX()*t+to->getPosX()*(1-t);
			float y=from->getPosY()*t+to->getPosY()*(1-t);

			float angle=from->getAngle()*t+to->getAngle()*(1-t);
			float sx=from->getScaleX()*t+to->getScaleX()*(1-t);
			float sy=from->getScaleY()*t+to->getScaleY()*(1-t);
			slerp->setPos(x,y);
			slerp->setAngle(angle);
			slerp->setScale(sx,sy);
            DsDebug<<"x:"<<x<<" y:"<<y<<" angle:"<<angle<<" sx:"<<sx<<" sy:"<<sy<<endl;
        }
		ret->pushFrameImage(slerp);
	}
    for(int i=image_nu;i<m_from->getFrameImageNu();i++)
	{
		DsFrameImage* img=m_from->getFrameImage(i);
		DsFrameImage* slerp=img->clone();
		ret->pushFrameImage(slerp);
	}
	return ret;
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










































