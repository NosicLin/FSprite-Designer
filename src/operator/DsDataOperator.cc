#include "DsDataOperator.h"

DsDataOperator::DsDataOperator()
{
	m_data=DsData::shareData();
}

void DsDataOperator::setCurProject(DsProject* prog)
{
	m_data->setCurProject(prog);
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

void DsDataOperator::addAnimation(const std::string& name)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
    {
        DsAnimation* anim=new DsAnimation(name);
		sprite->addAnimation(anim);
        m_data->emitSignal(DsData::SG_SPRITE_PROPERTY_CHANGE);
	}
}

void DsDataOperator::removeAnimation(const std::string& anim)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
	{
		/*TODO*/
	}
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











