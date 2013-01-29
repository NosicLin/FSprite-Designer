#include <assert.h>
#include <QtGui>
#include "DsEditState.h"
#include "DsEditView.h"
#include "operator/DsOperator.h"
#include "util/DsDebug.h"

void DsEditState::onEnter(DsEditState* prev)
{
}

void DsEditState::onExit(DsEditState* next)
{
}
void DsEditState::mouseMoveEvent(QMouseEvent* event)
{
}
void DsEditState::mousePressEvent(QMouseEvent* event)
{
}
void DsEditState::mouseReleaseEvent(QMouseEvent* event)
{
}
void DsEditState::wheelEvent(QMouseEvent* event)
{
}
void DsEditState::keyPressEvent(QKeyEvent* event)
{
}
void DsEditState::keyReleaseEvent(QKeyEvent* event)
{
}
void DsEditState::draw()
{
    DsDebug<<"draw"<<endl;
}

/* DsEditStateIdel */

DsEditStateIdel::DsEditStateIdel()
{
    m_type=DsEditState::ST_IDEL;
}

void DsEditStateIdel::mousePressEvent(QMouseEvent* event)
{
	if(event->buttons()&Qt::LeftButton)
	{
		DsData* data=DsData::shareData();
        DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
		if(cur_frame==NULL)
		{
			return;
		}

		float x=event->x();
		float y=event->y();
		m_editView->transformToRealCoord(&x,&y);

		DsFrameImage* cur_frameImg=data->getCurFrameImage();
		assert(cur_frameImg==NULL);

        DsKeyFrame::Iterator iter=cur_frame->begin();
		for(;iter!=cur_frame->end();++iter)
		{
			if((*iter)->hit(x,y))
			{
                DsDebug<<"hit:"<<(*iter)->getName().c_str()<<endl;
				DsOperator::data.setCurFrameImage((*iter)->getName());
                m_editView->changeToState(&m_editView->m_stateSelect);
			}
		}
	}
}

void DsEditStateIdel::draw()
{
    DsData* data=DsData::shareData();
    int cur_frame_index=data->getCurFrameIndex();
    DsDebug<<"Cur_frame_index:"<<cur_frame_index<<endl;
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
	if(!cur_frame)
	{
        DsDebug<<"cur_frame not finde"<<endl;
		return;
	}
	int image_nu=cur_frame->getFrameImageNu();

    //DsDebug<<"image_nu:"<<image_nu<<endl;
	for(int i=image_nu-1;i>=0;i--)
	{
		DsFrameImage* image=cur_frame->getFrameImage(i);
		m_editView->drawFrameImage(image);
	}
}


void DsEditStateSelect::mousePressEvent(QMouseEvent* event)
{
	if(event->buttons()&Qt::LeftButton)
	{
		float x=event->x();
		float y=event->y();
		m_editView->transformToRealCoord(&x,&y);
		DsData* data=DsData::shareData();
        DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
		assert(cur_frame!=NULL);

		DsFrameImage* cur_frameImg=data->getCurFrameImage();
		assert(cur_frameImg!=NULL);

		if(cur_frameImg->hit(x,y))
		{
			return;
		}

        DsKeyFrame::Iterator iter=cur_frame->begin();
		for(;iter!=cur_frame->end();++iter)
		{
			if((*iter)->hit(x,y))
			{
                DsDebug<<"hit:"<<(*iter)->getName().c_str()<<endl;
				DsOperator::data.setCurFrameImage((*iter)->getName());
				return;
			}
		}
    }
    DsOperator::data.dropCurFrameImage();

    m_editView->changeToState(&m_editView->m_stateIdel);
}

void DsEditStateSelect::draw()
{
	DsData* data=DsData::shareData();
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
    assert(((DsFrame*)cur_frame)->getType()==DsFrame::FRAME_KEY);

	DsFrameImage* cur_frameImg=data->getCurFrameImage();
	assert(cur_frameImg);

	int image_nu=cur_frame->getFrameImageNu();

    //DsDebug<<"image_nu:"<<image_nu<<endl;
	for(int i=image_nu-1;i>=0;i--)
	{
		DsFrameImage* image=cur_frame->getFrameImage(i);
		m_editView->drawFrameImage(image);
		if(image==cur_frameImg)
		{
			glPushMatrix();
			float x,y,width,height,sx,sy,angle;
			x=image->getPosX();
			y=image->getPosY();
			width=image->getWidth();
			height=image->getHeight();
			sx=image->getScaleX();
			sy=image->getScaleY();
			angle=image->getAngle();
			width*=sx;
			height*=sx;
			glTranslatef(x,y,0);
            glRotatef(angle,0,0,1);

			m_editView->setLineColor(1.0,0.0,0.0);
			m_editView->drawLine(-width/2,-height/2,width/2,-height/2);
			m_editView->drawLine(width/2,-height/2,width/2,height/2);
			m_editView->drawLine(-width/2,height/2,width/2,height/2);
			m_editView->drawLine(-width/2,height/2,-width/2,-height/2);
			glPopMatrix();
		}
	}
}



DsEditStateNotEdit::DsEditStateNotEdit()
{
	m_type=ST_NOT_EDIT;
}

void DsEditStateNotEdit::draw()
{
	DsData* data=DsData::shareData();
	assert(data->getCurFrame()->getType()==DsFrame::FRAME_TWEEN);
	DsTweenFrame* cur_frame=(DsTweenFrame*)data->getCurFrame();
	assert(cur_frame);

    DsKeyFrame* key_frame=cur_frame->slerpToKeyFrame(data->getCurFrameIndex());

    int image_nu=key_frame->getFrameImageNu();
    DsDebug<<"image_NU:"<<image_nu<<endl;
	for(int i=image_nu-1;i>=0;i--)
	{
        DsFrameImage* image=key_frame->getFrameImage(i);
        assert(image);
        //DsDebug<"ImageName:"<<image->getName().c_str()<<endl;
		m_editView->drawFrameImage(image);
	}
	delete key_frame;
}


















