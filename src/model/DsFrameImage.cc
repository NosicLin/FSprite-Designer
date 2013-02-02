#include <cmath>
#include <cstring>

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

static int s_id=0;
DsFrameImage::DsFrameImage(const std::string& name)
{
    char buf[128];
    sprintf(buf,"%d",s_id++);
    std::string unique=std::string("##")+std::string(buf);
    m_name=name+unique;
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
    char buf[128];
    sprintf(buf,"%d",s_id++);
    std::string unique=std::string("##")+std::string(buf);

    m_image=img;
    m_name=img->name+unique;

    m_width=img->image->width();
    m_height=img->image->height();
}

bool DsFrameImage::hit(float x,float y)
{
    x=x-m_tx;
    y=y-m_ty;

    float ks=sin(m_angle);
    float kc=cos(m_angle);

    float rx=kc*x-ks*y;
    float ry=ks*x+kc*y;

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
    DsFrameImage* ret=new DsFrameImage(m_name);
    *ret=*this;
    ret->setImage(this->m_image);
    return ret;
}




