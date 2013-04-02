#include <cmath>
#include <cstring>
#include <QMatrix4x4>
#include <QVector3D>

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

    /* translate*/
    m_tx=0;
    m_ty=0;

    /* scale */
    m_sx=1;
    m_sy=1;

    /* rotate */
    m_angle=0;

    /* texture area*/
    m_areax0=0;
    m_areay0=0;
    m_areax1=1.0;
    m_areay1=1.0;

    /* alpha */
    m_alpha=1.0f;


    /* offset */
    m_fx=0;
    m_fy=0;
}

void DsFrameImage::setImage(DsImage* img)
{
    m_image=img;
    m_width=img->image->width();
    m_height=img->image->height();
}

void DsFrameImage::getVertex(float* vx0,float* vy0,float* vx1,float* vy1)
{
    float rx0,ry0,rx1,ry1;

    rx0=m_width*m_areax0+m_fx-m_width/2;
    ry0=m_height*m_areay0+m_fy-m_height/2;
    rx1=m_width*m_areax1+m_fx-m_width/2;
    ry1=m_height*m_areay1+m_fy-m_height/2;

    if(rx0<rx1)
    {
        *vx0=rx0;
        *vx1=rx1;
    }
    else
    {
        *vx0=rx1;
        *vx1=rx0;
    }

    if(ry0<ry1)
    {
        *vy0=ry0;
        *vy1=ry1;
    }
    else
    {
        *vy0=ry1;
        *vy1=ry0;
    }
}
void DsFrameImage::transformVertexL(float* x,float* y)
{
    float ks=sin(m_angle/180.0f*3.1415926);
    float kc=cos(m_angle/180.0f*3.1415926);

    QMatrix4x4 tf(m_sx*kc,-m_sy*ks,0, m_tx,
                  m_sx*ks,m_sy*kc,0, m_ty,
                  0,      0,      1, 0,
                  0,      0,      0, 1);

    QMatrix4x4 vtf=tf.inverted();

    QVector3D v0(*x,*y,0);

    QVector3D v1=vtf.map(v0);
    *x=v1.x();
    *y=v1.y();
}
void DsFrameImage::transformVertexVL(float* x,float* y)
{
    float ks=sin(m_angle/180.0f*3.1415926);
    float kc=cos(m_angle/180.0f*3.1415926);

    QMatrix4x4 tf(m_sx*kc,-m_sy*ks,0, 0,
                  m_sx*ks,m_sy*kc,0, 0,
                  0,      0,      1, 0,
                  0,      0,      0, 1);

    QMatrix4x4 vtf=tf.inverted();

    QVector3D v0(*x,*y,0);

    QVector3D v1=vtf.map(v0);
    *x=v1.x();
    *y=v1.y();
}

void DsFrameImage::transformVertexW(float* x,float* y)
{
    float ks=sin(m_angle/180.0f*3.1415926);
    float kc=cos(m_angle/180.0f*3.1415926);

    QMatrix4x4 tf(m_sx*kc,-m_sy*ks,0, m_tx,
                  m_sx*ks,m_sy*kc,0, m_ty,
                  0,      0,      1, 0,
                  0,      0,      0, 1);

    QVector3D v0(*x,*y,0);
    QVector3D v1=tf.map(v0);
    *x=v1.x();
    *y=v1.y();
}
void DsFrameImage::transformVertexVW(float* x,float* y)
{
    float ks=sin(m_angle/180.0f*3.1415926);
    float kc=cos(m_angle/180.0f*3.1415926);

    QMatrix4x4 tf(m_sx*kc,-m_sy*ks,0, 0,
                  m_sx*ks,m_sy*kc,0, 0,
                  0,      0,      1, 0,
                  0,      0,      0, 1);

    QVector3D v0(*x,*y,0);
    QVector3D v1=tf.map(v0);
    *x=v1.x();
    *y=v1.y();
}


bool DsFrameImage::hit(float x,float y)
{
    transformVertexL(&x,&y);

    float vx0,vy0,vx1,vy1;
    getVertex(&vx0,&vy0,&vx1,&vy1);

    if((vx0<=x&&x<=vx1)||(vx1<=x&&x<=vx0))
    {
        if((vy0<=y&&y<=vy1)||(vy1<=y&&y<=vy0))
        {
            return true;
        }
    }
    return false;
}

DsFrameImage* DsFrameImage::clone(int clone_id)
{
    DsFrameImage* ret=new DsFrameImage;
    *ret=*this;
    if(clone_id)
    {
        ret->setID(this->m_id);
    }
    ret->setImage(this->m_image);
    return ret;
}

DsFrameImage& DsFrameImage::operator =(const DsFrameImage& image)
{
    this->m_image=image.m_image;
    this->m_width=image.m_width;
    this->m_height=image.m_height;
    this->m_tx=image.m_tx;
    this->m_ty=image.m_ty;
    this->m_sx=image.m_sx;
    this->m_sy=image.m_sy;
    this->m_angle=image.m_angle;
    this->m_areax0=image.m_areax0;
    this->m_areay0=image.m_areay0;
    this->m_areax1=image.m_areax1;
    this->m_areay1=image.m_areay1;
    this->m_alpha=image.m_alpha;
    this->m_fx=image.m_fx;
    this->m_fy=image.m_fy;
    return *this;
}


DsFrameImage* DsFrameImage::slerp(DsFrameImage* to,float t)
{

    DsFrameImage* slerp=this->clone();
    if(this->getImage()==to->getImage())
    {
        /* transform */
        float x=this->getPosX()*t+to->getPosX()*(1-t);
        float y=this->getPosY()*t+to->getPosY()*(1-t);

        float angle=this->getAngle()*t+to->getAngle()*(1-t);
        float sx=this->getScaleX()*t+to->getScaleX()*(1-t);
        float sy=this->getScaleY()*t+to->getScaleY()*(1-t);

        /* texture area */
        float ftx0,fty0,ftx1,fty1;
        float ttx0,tty0,ttx1,tty1;
        float rtx0,rty0,rtx1,rty1;
        this->getTextureArea(&ftx0,&fty0,&ftx1,&fty1);
        to->getTextureArea(&ttx0,&tty0,&ttx1,&tty1);

        rtx0=ftx0*t+ttx0*(1-t);
        rtx1=ftx1*t+ttx1*(1-t);
        rty0=fty0*t+tty0*(1-t);
        rty1=fty1*t+tty1*(1-t);


        /* offset */
        float fx=this->getOffsetX()*t+to->getOffsetX()*(1-t);
        float fy=this->getOffsetY()*t+to->getOffsetY()*(1-t);

        /* alpha */
        float alpha=this->getAlpha()*t+to->getAlpha()*(1-t);

        slerp->setPos(x,y);
        slerp->setAngle(angle);
        slerp->setScale(sx,sy);
        slerp->setOffset(fx,fy);
        slerp->setAlpha(alpha);
        slerp->setTextureArea(rtx0,rty0,rtx1,rty1);

    }
    return slerp;
}








