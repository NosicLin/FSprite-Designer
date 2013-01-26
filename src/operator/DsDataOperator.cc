#include "DsDataOperator.h"

DataOperator::DataOperator()
{
	m_data=DsData::shareData();
}

void DataOperator::setCurProject(DsProject* prog)
{
	m_data->setCurProject(prog);
    m_data->emitSignal(DsData::SG_CUR_PROJECT_CHANGE);
}

void DataOperator::setCurAnimation(const std::string& anim)
{
	m_data->setCurAnimation(anim);
    m_data->emitSignal(DsData::SG_CUR_ANIMATION_CHANGE);
}

void DataOperator::setCurFrame(int frame)
{
	m_data->setCurFrame(frame);
    m_data->emitSignal(DsData::SG_CUR_FRAME_CHANGE);
}

void DataOperator::setCurFrameImage(const std::string& anim)
{
	m_data->setCurFrameImage(anim);
    m_data->emitSignal(DsData::SG_CUR_FRAME_IMAGE_CHANGE);
}

void DataOperator::addAnimation(const std::string& name)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
    {
        DsAnimation* anim=new DsAnimation(name);

		sprite->addAnimation(anim);
        m_data->emitSignal(DsData::SG_SPRITE_PROPERTY_CHANGE);
	}
}

void DataOperator::removeAnimation(const std::string& anim)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
	{
		/*TODO*/
	}
}



