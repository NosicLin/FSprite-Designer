#include <assert.h>
#include "DsDataOperator.h"
#include "util/DsDebug.h"

void DsDataOperator::newProject()
{
	DsSprite* sprite=new DsSprite;
	DsProject* proj=new DsProject(sprite,"untitled");
	m_data->addProject(proj);
	m_data->emitSignal(DsData::SG_DATA_PROPERTY_CHANGE);
	m_data->setCurProject(proj->getName());
	m_data->emitSignal(DsData::SG_CUR_PROJECT_CHANGE);
}


DsDataOperator::DsDataOperator()
{
	m_data=DsData::shareData();
}

void DsDataOperator::setCurProject(const std::string& name)
{
    m_data->setCurProject(name);
    m_data->emitSignal(DsData::SG_CUR_PROJECT_CHANGE);
}

void DsDataOperator::setCurAnimation(const std::string& anim)
{
	m_data->setCurAnimation(anim);
    m_data->emitSignal(DsData::SG_CUR_ANIMATION_CHANGE);
}

void DsDataOperator::setCurFrameIndex(int frame)
{
    m_data->setCurFrameIndex(frame);
    m_data->emitSignal(DsData::SG_CUR_FRAME_CHANGE);
}

void DsDataOperator::setCurFrameImage(const std::string& anim)
{
	m_data->setCurFrameImage(anim);
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

        }
    }

}
void DsDataOperator::removeCurFrameImage()
{
    DsFrameImage* cur=m_data->getCurFrameImage();
    if(cur)
    {
        DsKeyFrame* frame=(DsKeyFrame*) m_data->getCurFrame();
        frame->removeFrameImage(cur->getName());
        m_data->dropCurFrameImage();

        m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
    }
}

void DsDataOperator::addAnimation(const std::string& name)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
    {
        DsAnimation* anim=new DsAnimation(name);
		sprite->addAnimation(anim);
        m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
	}
}

void DsDataOperator::removeAnimation(const std::string& anim)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
	{
		DsAnimation* cur_anim=m_data->getCurAnimation();
		if(cur_anim->getName()==anim)
		{
			m_data->dropCurAnimation();
		}
		sprite->removeAnimation(anim);
		m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
	}
}
/*
void  DsDataOperator::renameAnimation(
				const std::string& target_name)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
	{
		DsAnimation* cur_anim=m_data->getCurAnimation();
		if(sprite->hasAnimation(target_name))
		{
			std::string rename_target;
			int i=0;
			do 
			{
				rename_target=target_name+"("+QString::number(i)+")";
				i++;
			}while(sprite->hasAnimation(rename_target));
			cur_anim->setName(rename_target);
		}
		else 
		{
			cur_anim->setName(target_name);
		}
		m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
	}
}
*/



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
            if(!sprite->hasAnimation(name))
            {
                DsAnimation* anim;
                anim=DsAnimation::createWithFirstFrame(name);
                sprite->addAnimation(anim);
                m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
                m_data->setCurAnimation(name);
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

    frame->upFrameImage(cur->getName());
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

    frame->downFrameImage(cur->getName());
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

    frame->frameImageToEnd(cur->getName());
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

    frame->frameImageToFront(cur->getName());
    m_data->emitSignal(DsData::SG_FRAME_PROPERTY_CHANGE);
}
































