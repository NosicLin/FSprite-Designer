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
    DsFrame* frame=sprite_info->getCurFrame();
    if(frame==NULL)
    {
        return ;
    }
    if(frame->getType()!=DsFrame::FRAME_KEY)
    {
        return ;
    }

    m_data->saveState();
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

bool DsAuxOperator::canCopyFrame()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info==NULL)
    {
        return false;
    }
    int frame_index=sprite_info->getCurFrameIndex();
    if(frame_index==-1)
    {
        return false;
    }

    DsFrame* frame=sprite_info->getCurFrame();
    if(frame==NULL)
    {
        return false;
    }
    return true;

}

bool DsAuxOperator::canPasteFrame()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info==NULL)
    {
        return false;
    }
    DsAnimation* anim=sprite_info->getCurAnimation();
    if(anim==NULL)
    {
        return false;
    }
    int frame_index=sprite_info->getCurFrameIndex();
    if(frame_index==-1)
    {
        return false;
    }

    DsKeyFrame* frame=sprite_info->getCopyFrame();
    if(frame==NULL)
    {
        return false;
    }
    return true;
}

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
    DsKeyFrame* copy=NULL;

    if(frame==NULL)
    {
        return;
    }
    if(frame->getType()==DsFrame::FRAME_TWEEN)
    {
        copy=((DsTweenFrame*)frame)->slerpToKeyFrame(frame_index);
    }
    else
    {
        copy=((DsKeyFrame*)frame)->clone();
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
    int frame_index=sprite_info->getCurFrameIndex();
    if(frame_index==-1)
    {
        return ;
    }

    DsKeyFrame* frame=sprite_info->getCopyFrame();
    if(frame==NULL)
    {
        return ;
    }

    m_data->saveState();
    DsKeyFrame* copy=frame->clone();
    anim->insertKeyFrame(frame_index,copy);
    m_data->emitSignal(DsData::SG_ANIMATION_PROPERTY_CHANGE);
}



void DsAuxOperator::redo()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info!=NULL)
    {
        sprite_info->redo();
        m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
    }

}
void DsAuxOperator::undo()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info!=NULL)
    {
        sprite_info->undo();
        m_data->emitSignal(DsData::SG_PROJECT_PROPERTY_CHANGE);
    }
}

bool DsAuxOperator::canRedo()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info==NULL)
    {
        return  false;
    }
    return sprite_info->canRedo();
}
bool DsAuxOperator::canUndo()
{
    DsProject::DsSpriteInfo* sprite_info=m_data->getCurSpriteInfo();
    if(sprite_info==NULL)
    {
        return  false;
    }
    return sprite_info->canUndo();
}
































