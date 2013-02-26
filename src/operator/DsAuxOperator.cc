#include "DsAuxOperator.h"
#include "DsOperator.h"
#include "model/DsFrame.h"

DsAuxOperator::DsAuxOperator()
{
	m_data=DsData::shareData();
}


void DsAuxOperator::pasteFrameImage()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
	if(sprite_info==NULL)
    {
        return ;
    }
    DsFrameImage* copy=sprite_info->getCopyFrameImage();
    if(copy==NULL)
    {
        return ;
    }
    DsFrameImage* copy2=copy->clone();
    DsOperator::data()->addFrameImage(copy2);
}

void DsAuxOperator::copyFrameImage()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info==NULL)
    {
        return;
    }
    DsFrameImage* cur_frame_img=sprite_info->getCurFrameImage();
    if(cur_frame_img==NULL)
    {
        return;
    }
    DsFrameImage* copy=cur_frame_img->clone();
    sprite_info->setCopyFrameImage(copy);
}


/*
void DsAuxOperator::copyFrame()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info==NULL)
    {
        return ;
    }
    int frame_index=sprite_info->getCurFrameIndex();
    if(frame_index==-1)
    {
        return ;
    }

    DsFrame* frame=sprite_info->getCurFrame();
    DsFrame* copy=NULL;

    if(frame->getType()==DsFrame::FRAME_TWEEN)
    {
        copy=((DsFrameTween*)frame)->slerp(frame_index);
    }
    else
    {
        copy=((DsFrameKey*)frame)->clone();
    }
    sprite_info->setCopyFrame(copy);
}
void DsAuxOperator::pasteFrame()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info==NULL)
    {
        return;
    }
    DsAnimation* anim=sprite_info->getCurAnimation();
    if(anim==NULL)
    {
        return ;
    }
    int frame_index=sprite_info->getFrameIndex();
    if(frame_index==-1)
    {
        return ;
    }

    DsFrame* frame=sprite_info->getCopyFrame();
    if(frame==NULL)
    {
        return ;
    }

    DsFrame* copy=frame->clone();

    anim->insertKeyFrame(frame_index,copy);
    m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
}

*/























