#include "DsData.h"
#include "assert.h"

DsData* s_shareData=NULL;

DsData* DsData::shareData()
{
	if(s_shareData==NULL)
	{
		s_shareData=new DsData;
	}
	return s_shareData;
}


DsData::DsData()
{
    m_curProject=NULL;
}

void DsData::emitSignal(int type)
{

	switch(type)
	{
        case SG_CUR_PROJECT_CHANGE:
			emit signalCurProjectChange();
			break;
		case SG_CUR_ANIMATION_CHANGE:
			emit signalCurAnimationChange();
			break;
		case SG_CUR_FRAME_CHANGE:
			emit signalCurFrameChange();
			break;
		case SG_CUR_FRAME_IMAGE_CHANGE:
			emit signalCurFrameImageChange();
			break;


		case SG_PROJECT_PROPERTY_CHANGE:
			emit signalProjectPropertyChange();
			break;

		case SG_SPRITE_PROPERTY_CHANGE:
			emit signalSpritePropertyChange();
			break;

		case SG_ANIMATION_PROPERTY_CHANGE:
			emit signalAnimationPropertyChange();
			break;

		case SG_FRAME_PROPERTY_CHANGE:
			emit signalFramePropertyChange();
			break;
		case SG_FRAME_IMAGE_PROPERTY_CHANGE:
			emit signalFrameImagePropertyChange();
			break;

		default:
			assert(0);
	}
}













