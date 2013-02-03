#include <stdio.h>
#include <assert.h>

#include "DsProject.h"
#include "DsAnimation.h"
#include "DsSprite.h"

DsProject::DsProject(DsSprite* sprite,std::string name)
{
    static int s_id=0;
    char buf[128];

    sprintf(buf,"##%d",s_id++);
    m_realName=name;

    m_name=name+std::string(buf);

    m_sprite=sprite;
    m_curAnimation=NULL;
    m_curFrameIndex=-1;
    m_curFrameImage=NULL;
}

void DsProject::setCurAnimation(const std::string& name)
{
    m_curAnimation=m_sprite->getAnimation(name);
    assert(m_curAnimation);

    if(m_curAnimation->getFrameNu()>0)
    {
        m_curFrameIndex=0;
    }
    else
    {
        m_curFrameIndex=-1;
    }
    m_curFrameImage=NULL;
}

void DsProject::setCurFrameIndex(int frame)
{
    if(!m_curAnimation)
    {
        return;
    }
    m_curFrameIndex=frame;
    m_curFrameImage=NULL;
}

void DsProject::setCurFrameImage(const std::string& name)
{
    if(m_curFrameIndex==-1)
    {
        return;
    }
    DsFrame* frame=m_curAnimation->getFrame(m_curFrameIndex);
    assert(frame);
    assert(frame->getType()==DsFrame::FRAME_KEY);
    m_curFrameImage=((DsKeyFrame*)frame)->getFrameImage(name);
    assert(m_curFrameImage);
}


void DsProject::dropCurAnimation()
{
    m_curAnimation=NULL;
    m_curFrameIndex=-1;
    m_curFrameImage=NULL;
}
void DsProject::dropCurFrameIndex()
{
    m_curFrameIndex=-1;
    m_curFrameImage=NULL;
}
void DsProject::dropCurFrameImage()
{
    m_curFrameImage=NULL;
}


DsFrame* DsProject::getCurFrame()
{
    if(!m_curAnimation)
    {
        return NULL;
    }
    if(m_curFrameIndex==-1)
    {
        return NULL;
    }

    return m_curAnimation->getFrame(m_curFrameIndex);
}






