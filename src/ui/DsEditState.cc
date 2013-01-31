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
    else if(event->key()==Qt::Key_S)
	{
        m_editView->changeToState(&m_editView->m_stateScale);
	}
    else if(event->key()==Qt::Key_R)
    {
        m_editView->changeToState(&m_editView->m_stateRotate);
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
            glScalef(sx,sy,1);
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

void DsEditStateScale::onEnter(DsEditState* s)
{
    QPoint  coord=m_editView->m_lastpos;
	m_startx =coord.x();
    m_starty=coord.y();
    m_nowx=m_startx;
    m_nowy=m_starty;
	m_direction=DsEditState::DIRECTION_BOTH;
}
DsEditStateScale::DsEditStateScale()
{
    m_startx=0;
    m_starty=0;
    m_nowx=0;
    m_nowy=0;
    m_direction=DsEditState::DIRECTION_BOTH;
}

void DsEditStateScale::keyPressEvent(QKeyEvent* event)
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
            m_direction=DsEditState::DIRECTION_BOTH;
        }
    }

}


void DsEditStateScale::mouseMoveEvent(QMouseEvent* event)
{
    QPoint last_pos=m_editView->m_lastpos;
	m_nowx=last_pos.x();
    m_nowy=last_pos.y();
}

float DsEditStateScale::getScale()
{
    DsData* data=DsData::shareData();
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
    DsFrameImage* cur_frameImg=data->getCurFrameImage();

    float x=cur_frameImg->getPosX();
    float y=cur_frameImg->getPosY();
    m_editView->transformToWidgetCoord(&x,&y);

    float startds=sqrt((m_startx-x)*(m_startx-x)+(m_starty-y)*(m_starty-y));
    float nowds=sqrt((m_nowx-x)*(m_nowx-x)+(m_nowy-y)*(m_nowy-y));

    DsDebug<<"x:"<<x<<" y:"<<y<<" startds:"<<startds<<" nowds:"<<nowds;
    DsDebug<<" m_startx:"<<m_startx<<" m_starty:"<<m_starty<<" m_nowx:"<<m_nowx<<" m_nowy:"<<m_nowy<<endl;

    if(startds==0) { startds=1; }
    if(nowds==0) { nowds=1; }

    return nowds/startds;
}

void DsEditStateScale::mousePressEvent(QMouseEvent* event)
{
    DsData* data=DsData::shareData();
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
    assert(((DsFrame*)cur_frame)->getType()==DsFrame::FRAME_KEY);

    DsFrameImage* cur_frameImg=data->getCurFrameImage();
    float sx=cur_frameImg->getScaleX();
    float sy=cur_frameImg->getScaleY();

    float scale=getScale();
    if(event->buttons()&Qt::LeftButton)
    {
        if(m_direction==DsEditState::DIRECTION_X)
        {
            sx*=scale;
        }
        else if(m_direction==DsEditState::DIRECTION_Y)
        {
            sy*=scale;
        }
        else
        {
            sx*=scale;
            sy*=scale;
        }
        DsOperator::data.setCurFrameImageScale(sx,sy);
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
    else if(event->buttons()&Qt::RightButton)
    {
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
}

void DsEditStateScale::draw()
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
            float scale=getScale();
            glPushMatrix();

            float x,y,width,height,sx,sy,angle;
            x=image->getPosX();
            y=image->getPosY();

            sx=image->getScaleX();
            sy=image->getScaleY();
            width=image->getWidth();
            height=image->getHeight();

            angle=image->getAngle();

            if(m_direction==DsEditState::DIRECTION_X)
            {
                sx*=scale;
            }
            else if(m_direction==DsEditState::DIRECTION_Y)
            {
                sy*=scale;
            }
            else
            {
                sx*=scale;
                sy*=scale;
            }

            glTranslatef(x,y,0);
            glRotatef(angle,0,0,1);
            glScalef(sx,sy,1);

            m_editView->rawDrawFrameImage(image);

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


DsEditStateRotate::DsEditStateRotate()
{
    m_angle=0;
}

void DsEditStateRotate::onEnter(DsEditState* )
{
    m_angle=0;
}

void DsEditStateRotate::mouseMoveEvent(QMouseEvent* event)
{
    DsData* data=DsData::shareData();
    DsFrameImage* cur_frameImg=data->getCurFrameImage();

    float ox=cur_frameImg->getPosX();
    float oy=cur_frameImg->getPosY();
    m_editView->transformToWidgetCoord(&ox,&oy);

    QPoint last_pos=m_editView->m_lastpos;
    float fx=last_pos.x();
    float fy=last_pos.y();

    float tx=event->x();
    float ty=event->y();

    DsDebug<<"fx:"<<fx<<" fy:"<<fy<<" tx:"<<tx<<" ty:"<<ty<<" ox:"<<ox<<" oy:"<<oy<<endl;

    float vfx=fx-ox;
    float vfy=fy-oy;

    float vtx=tx-ox;
    float vty=ty-oy;

    float dg=(vfx*vtx+vfy*vty)/(sqrt(vfx*vfx+vfy*vfy)*sqrt(vtx*vtx+vty*vty));

    int direction=vtx*vfy-vty*vfx<0?-1:1;

    float theta=acos(dg)/3.1415925*180.0f;
    m_angle+=theta*direction;

}
void DsEditStateRotate::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        DsData* data=DsData::shareData();

        DsFrameImage* cur_frameImg=data->getCurFrameImage();
        assert(cur_frameImg);

        float g=cur_frameImg->getAngle();
        DsOperator::data.setCurFrameImageAngle(g+m_angle);
        m_editView->changeToState(&m_editView->m_stateSelect);
    }

    else if(event->buttons()&Qt::RightButton)
    {
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
}
void DsEditStateRotate::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Escape)
    {
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
}

void DsEditStateRotate::draw()
{
    DsData* data=DsData::shareData();
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
    DsFrameImage* cur_frameImg=data->getCurFrameImage();

    int image_nu=cur_frame->getFrameImageNu();

    for(int i=image_nu-1;i>=0;i--)
    {
        DsFrameImage* image=cur_frame->getFrameImage(i);

        if(image==cur_frameImg)
        {
            glPushMatrix();

            float x,y,width,height,sx,sy,angle;
            x=image->getPosX();
            y=image->getPosY();

            sx=image->getScaleX();
            sy=image->getScaleY();
            width=image->getWidth();
            height=image->getHeight();

            angle=image->getAngle();
            angle+=m_angle;

            glTranslatef(x,y,0);
            glRotatef(angle,0,0,1);
            glScalef(sx,sy,1);

            m_editView->rawDrawFrameImage(image);

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








































