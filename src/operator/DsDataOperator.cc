#include <assert.h>
#include "DsDataOperator.h"
#include "util/DsDebug.h"


void DsDataOperator::newSprite()
{
    DsProject* proj=m_data->getProject();
    if(proj)
    {
        char buf[120];
        int i=0;
        std::string  sprite_name="untile-sprite";
        while(proj->hasSpriteWithName(sprite_name))
        {
            sprintf(buf,"untile-sprite%d",i);
            sprite_name=buf;
            i++;
        }
        DsSprite* sprite=new DsSprite(sprite_name);
        proj->addSprite(sprite);

        m_data->setCurSprite(sprite->getID());
        m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
    }
}
void DsDataOperator::removeSprite(const std::string& id)
{
    DsProject* project=m_data->getProject();
    if(project)
    {
        project->removeSprite(id);
        m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
    }
}
bool DsDataOperator::renameSprite(const std::string& id,const std::string& name)
{
    DsProject* project=m_data->getProject();
    if(project)
    {
        DsSprite* sprite=project->getSprite(id);
        assert(sprite);

        if(sprite->getName()==name)
        {
            return true;
        }
        if(project->hasSpriteWithName(name))
        {
            return false;
        }

        sprite->setName(name);
        m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
    }
    return false;
}



DsDataOperator::DsDataOperator()
{
    m_data=DsData::shareData();
}

void DsDataOperator::setCurSprite(const std::string& id)
{
    m_data->setCurSprite(id);
    m_data->emitSignal(DsData::SG_CUR_SPRITE_CHANGE);
}

void DsDataOperator::setCurAnimation(const std::string& id)
{
    m_data->setCurAnimation(id);
    m_data->emitSignal(DsData::SG_CUR_ANIMATION_CHANGE);
}


void DsDataOperator::setCurFrameIndex(int frame)
{
    m_data->setCurFrameIndex(frame);
    m_data->emitSignal(DsData::SG_CUR_FRAME_CHANGE);
}



void DsDataOperator::setCurFrameImage(const std::string& id)
{
    m_data->setCurFrameImage(id);
    m_data->emitSignal(DsData::SG_CUR_FRAME_IMAGE_CHANGE);
}


void DsDataOperator::addFrameImage(DsFrameImage* image)
{
    DsFrame* frame=m_data->getCurFrame();
    if(frame)
    {
        if(frame->getType()==DsFrame::FRAME_KEY)
        {
            ((DsKeyFrame*)frame)->insertFrameImage(image,0);
            m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
            return ;
        }
    }
    assert(0); /*never reach here */
}

void DsDataOperator::removeCurFrameImage()
{
    DsFrameImage* cur=m_data->getCurFrameImage();
    if(cur)
    {
        DsKeyFrame* frame=(DsKeyFrame*) m_data->getCurFrame();
        frame->removeFrameImage(cur->getID());
        m_data->dropCurFrameImage();
        m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
    }
}


void DsDataOperator::removeAnimation(const std::string& id)
{
    DsSprite* sprite=m_data->getCurSprite();
    if(sprite)
    {
        DsAnimation* cur_anim=m_data->getCurAnimation();
        if(cur_anim->getID()==id)
        {
            m_data->dropCurAnimation();
        }
        sprite->removeAnimation(id);
        m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
    }
}

bool DsDataOperator::renameAnimation(
                const std::string& sprite_id,
                const std::string& animation_id,
                const std::string& name)
{
    DsProject* project= m_data->getProject();
    if(project)
    {
        DsSprite* sprite=project->getSprite(sprite_id);
        assert(sprite);
        DsAnimation* anim=sprite->getAnimation(animation_id);
        assert(anim);
        if(anim->getName()==name)
        {
            return true ;
        }
        if(sprite->hasAnimationWithName(name))
        {
            return false;
        }
        else
        {
            anim->setName(name);
            return true;
            m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
        }
    }
    return false;

}



void DsDataOperator::dropCurFrameImage()
{
    DsFrameImage* image=m_data->getCurFrameImage();
    if(image!=NULL)
    {
        m_data->dropCurFrameImage();
        m_data->emitSignal(DsData::SG_CUR_FRAME_IMAGE_CHANGE);
    }
}


void DsDataOperator::insertKeyFrame(int index)
{
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim)
    {
        anim->insertKeyFrame(index);
        m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
    }
}

void DsDataOperator::insertEmptyKeyFrame(int index)
{
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim)
    {
        anim->insertEmptyKeyFrame(index);
        m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
    }
}


void DsDataOperator::removeKeyFrame(int index)
{
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim)
    {
        anim->removeKeyFrame(index);
        m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
    }
}
void DsDataOperator::removeRangeFrame(int from,int to)
{
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim)
    {
        for(int i=from;i<=to;i++)
        {
            DsFrame* frame=anim->getFrame(i);
            if(frame==NULL)
            {
                continue;
            }
            if(frame->getType()==DsFrame::FRAME_KEY)
            {
                if(frame->getFrameId()==i)
                {
                    anim->removeKeyFrame(i);
                }
            }
        }
        m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
    }
}


void DsDataOperator::insertTween(int index)
{
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim)
    {
        anim->insertTween(index);
        m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
    }
}

void DsDataOperator::removeTween(int index)
{
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim)
    {
        anim->removeTween(index);
        m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
    }
}
void DsDataOperator::tweenToKeyFrame(int index)
{
    DsAnimation* anim=m_data->getCurAnimation();
    if(anim)
    {
        DsFrame* frame=anim->getFrame(index);
        assert(frame);
        assert(frame->getType()==DsFrame::FRAME_TWEEN);
        DsTweenFrame* tween=(DsTweenFrame*)frame;
        int from=tween->getFromKeyFrame()->getFrameId();
        int to=tween->getToKeyFrame()->getFrameId();
        for(int i=from+1;i<to;i++)
        {
            anim->insertKeyFrame(i);
        }
        m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
    }
}



void DsDataOperator::setCurFrameImagePos(float x,float y)
{
    DsFrameImage* img=m_data->getCurFrameImage();
    if(img)
    {
        img->setPos(x,y);
        m_data->emitSignal(DsData::SG_FRAME_IMAGE_PROPERTY_CHANGE);
    }
}

void DsDataOperator::setCurFrameImageScale(float x,float y)
{
    DsFrameImage* img=m_data->getCurFrameImage();
    if(img)
    {
        img->setScale(x,y);
        m_data->emitSignal(DsData::SG_FRAME_IMAGE_PROPERTY_CHANGE);
    }
}

void DsDataOperator::setCurFrameImageAngle(float angle)
{
    DsFrameImage* img=m_data->getCurFrameImage();
    if(img)
    {
        img->setAngle(angle);
        m_data->emitSignal(DsData::SG_FRAME_IMAGE_PROPERTY_CHANGE);
    }
}
void DsDataOperator::setCurFrameImageOffset(float fx,float fy)
{
    DsFrameImage* img=m_data->getCurFrameImage();
    if(img)
    {
        img->setOffset(fx,fy);
        m_data->emitSignal(DsData::SG_FRAME_IMAGE_PROPERTY_CHANGE);
    }
}
void DsDataOperator::setCurFrameImageTextureArea(float cx0,float cy0,float cx1,float cy1)
{
    DsFrameImage* img=m_data->getCurFrameImage();
    if(img)
    {
        img->setTextureArea(cx0,cy0,cx1,cy1);
        m_data->emitSignal(DsData::SG_FRAME_IMAGE_PROPERTY_CHANGE);
    }
}

void DsDataOperator::setCurFrameImageAlpha(float alpha)
{
    DsFrameImage* img=m_data->getCurFrameImage();
    if(img)
    {
        img->setAlpha(alpha);
        m_data->emitSignal(DsData::SG_FRAME_IMAGE_PROPERTY_CHANGE);
    }
}

void DsDataOperator::newAnimation()
{
    DsSprite* sprite=m_data->getCurSprite();
    if(sprite)
    {
        int i=0;
        while(true)
        {
            QString qname=QString("anim")+QString::number(i);
            std::string name=qname.toStdString();
            if(!sprite->hasAnimationWithName(name))
            {
                DsAnimation* anim;
                anim=DsAnimation::createWithFirstFrame(name);
                sprite->addAnimation(anim);
                m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
                m_data->setCurAnimation(anim->getID());
                m_data->emitSignal(DsData::SG_CUR_ANIMATION_CHANGE);
                break;
            }
            i++;
        }
    }

}


void DsDataOperator::frameImageMoveUp()
{
    DsFrameImage* cur=m_data->getCurFrameImage();
    if(!cur)
    {
        DsDebug<<"Cur Frame Image Not Selected"<<endl;
        return;
    }
    DsKeyFrame* frame=(DsKeyFrame*)m_data->getCurFrame();

    frame->upFrameImage(cur->getID());
    m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
}

void DsDataOperator::frameImageMoveDown()
{
    DsFrameImage* cur=m_data->getCurFrameImage();
    if(!cur)
    {
        DsDebug<<"Cur Frame Image Not Selected"<<endl;
        return;
    }
    DsKeyFrame* frame=(DsKeyFrame*)m_data->getCurFrame();

    frame->downFrameImage(cur->getID());
    m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
}

void DsDataOperator::frameImageMoveEnd()
{
    DsFrameImage* cur=m_data->getCurFrameImage();
    if(!cur)
    {
        DsDebug<<"Cur Frame Image Not Selected"<<endl;
        return;
    }
    DsKeyFrame* frame=(DsKeyFrame*)m_data->getCurFrame();

    frame->frameImageToEnd(cur->getID());
    m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
}

void DsDataOperator::frameImageMoveFront()
{
    DsFrameImage* cur=m_data->getCurFrameImage();
    if(!cur)
    {
        DsDebug<<"Cur Frame Image Not Selected"<<endl;
        return;
    }
    DsKeyFrame* frame=(DsKeyFrame*)m_data->getCurFrame();

    frame->frameImageToFront(cur->getID());
    m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
}
































