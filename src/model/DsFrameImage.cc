#include <cmath>
#include <cstring>

#include "DsFrameImage.h"
#include "DsResourceMgr.h"
#include "DsData.h"
#include "util/DsDebug.h"
#include "util/DsUtil.h"


DsFrameImage::~DsFrameImage()
{
}

DsFrameImage* DsFrameImage::create(const std::string& img_name)
{
    DsImage* image=DsResourceMgr::loadImage(img_name);
    DsFrameImage* ret=new DsFrameImage;
    ret->setImage(image);
    return ret;
}

DsFrameImage::DsFrameImage()
{
    m_id=DsUtil::uniqueStringID();
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

bool DsFrameImage::hit(float x,float y)
{
    x=x-m_tx;
    y=y-m_ty;

    float ks=sin(m_angle/180.0f*3.1415926);
    float kc=cos(m_angle/180.0f*3.1415926);

    float rx=kc*x+ks*y;
    float ry=-ks*x+kc*y;
    DsDebug<<"rx:"<<rx<<" ry:"<<ry<<" angle:"<<m_angle<<endl;

    if(abs(rx)<m_width/2*m_sx)
    {
        if(abs(ry)<m_height/2*m_sy)
        {
            return true;
        }
    }

    return false;
}

DsFrameImage* DsFrameImage::clone()
{
    DsFrameImage* ret=new DsFrameImage;
    *ret=*this;
    ret->setImage(this->m_image);
    return ret;
}

