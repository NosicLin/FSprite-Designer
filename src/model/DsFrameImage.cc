#include "DsFrameImage.h"
#include "DsResourceMgr.h"
#include "DsData.h"

DsFrameImage::~DsFrameImage()
{
}

DsFrameImage* DsFrameImage::create(const std::string& img_name)
{
    DsImage* image=DsResourceMgr::loadImage(img_name);
    DsFrameImage* ret=new DsFrameImage(img_name);
    ret->setImage(image);
    return ret;
}

DsFrameImage::DsFrameImage(const std::string& name)
{
	m_name=name;
	m_image=NULL;
	m_width=0;
	m_height=0;
	m_tx=0;
	m_ty=0;
    m_sx=1;
    m_sy=1;
	m_angle=0;
	m_areax0=0;
	m_areay0=0;
	m_areax1=1;
	m_areay1=1;
}

void DsFrameImage::setImage(DsImage* img)
{
	m_image=img;
    m_width=img->image->width();
    m_height=img->image->height();
}



