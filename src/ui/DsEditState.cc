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
    if(event->buttons()&Qt::RightButton)
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



/* DsEditStateSelect */

void DsEditStateSelect::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()&Qt::RightButton)
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
void DsEditStateSelect::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_G)
    {
        m_editView->changeToState(&m_editView->m_stateTranslate);
    }
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


/* DsEditStateNotEdit */

DsEditStateNotEdit::DsEditStateNotEdit()
{
    m_type=ST_NOT_EDIT;
    m_prev=Qt::ArrowCursor;
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
void DsEditStateNotEdit::onEnter(DsEditState* s)
{
    m_prev=m_editView->cursor();
    m_editView->setCursor(Qt::ForbiddenCursor);
}
void DsEditStateNotEdit::onExit(DsEditState* s)
{
    m_editView->setCursor(m_prev);
}







/*  DsEditStateTranslate */
DsEditStateTranslate::DsEditStateTranslate()
{
    m_movex=0;
    m_movey=0;
    m_direction=DsEditState::DIRECTION_BOTH;
}
void DsEditStateTranslate::onEnter(DsEditState* prev)
{
    m_movex=0;
    m_movey=0;
    m_direction=DsEditState::DIRECTION_BOTH;
}

void DsEditStateTranslate::mouseMoveEvent(QMouseEvent* event)
{
    QPoint last_pos=m_editView->m_lastpos;
    float dx=event->x()-last_pos.x();
    float dy=event->y()-last_pos.y();

    m_movex+=dx;
    m_movey+=-dy;
}

void DsEditStateTranslate::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        DsData* data=DsData::shareData();
        DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
        assert(((DsFrame*)cur_frame)->getType()==DsFrame::FRAME_KEY);

        DsFrameImage* cur_frameImg=data->getCurFrameImage();
        assert(cur_frameImg);
        float x=cur_frameImg->getPosX();
        float y=cur_frameImg->getPosY();

        if(m_direction==DsEditState::DIRECTION_X)
        {
            x+=m_movex;
        }
        else if(m_direction==DsEditState::DIRECTION_Y)
        {
            y+=m_movey;
        }
        else
        {
            x+=m_movex;
            y+=m_movey;
        }
        DsOperator::data.setCurFrameImagePos(x,y);
        m_editView->changeToState(&m_editView->m_stateSelect);

    }
    else if(event->buttons()&Qt::RightButton)
    {
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
}

void DsEditStateTranslate::keyPressEvent(QKeyEvent* event)
{
    if(m_direction==DsEditState::DIRECTION_BOTH)
    {
        if(event->key()==Qt::Key_X)
        {
            m_direction=DsEditState::DIRECTION_X;
        }
        else if(event->key()==Qt::Key_Y)
        {
            m_direction=DsEditState::DIRECTION_Y;
        }
        else if(event->key()==Qt::Key_Escape)
        {
            m_editView->changeToState(&m_editView->m_stateSelect);
        }
    }
    else if(m_direction==DsEditState::DIRECTION_X)
    {
        if(event->key()==Qt::Key_Y)
        {
            m_direction=DsEditState::DIRECTION_Y;
        }
        else if(event->key()==Qt::Key_Escape)
        {
            m_movey=0;
            m_direction=DsEditState::DIRECTION_BOTH;
        }
    }
    else if(m_direction==DsEditState::DIRECTION_Y)
    {
        if(event->key()==Qt::Key_X)
        {
            m_direction=DsEditState::DIRECTION_X;
        }
        else if(event->key()==Qt::Key_Escape)
        {
            m_movex=0;
            m_direction=DsEditState::DIRECTION_BOTH;
        }
    }

}

void DsEditStateTranslate::draw()
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

        if(image==cur_frameImg)
        {

            glPushMatrix();
            if(m_direction==DsEditState::DIRECTION_X)
            {
                glTranslatef(m_movex,0,0);

            }
            else if(m_direction==DsEditState::DIRECTION_Y)
            {
                glTranslatef(0,m_movey,0);
            }
            else
            {
                glTranslatef(m_movex,m_movey,0);
            }

            m_editView->drawFrameImage(image);

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
            if(m_direction==DsEditState::DIRECTION_X)
            {

                m_editView->setLineColor(0.0,0.0,1.0);
                m_editView->drawLine(-100000,0,100000,0);
            }
            else if(m_direction==DsEditState::DIRECTION_Y)
            {
                m_editView->setLineColor(0.0,0.0,1.0);
                m_editView->drawLine(0,100000,0,-100000);
            }
            glRotatef(angle,0,0,1);

            m_editView->setLineColor(1.0,0.0,0.0);
            m_editView->drawLine(-width/2,-height/2,width/2,-height/2);
            m_editView->drawLine(width/2,-height/2,width/2,height/2);
            m_editView->drawLine(-width/2,height/2,width/2,height/2);
            m_editView->drawLine(-width/2,height/2,-width/2,-height/2);
            glPopMatrix();
        }
        else
        {
            m_editView->drawFrameImage(image);
        }

    }
}














