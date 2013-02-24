#include <assert.h>
#include <QtGui>
#include "DsEditState.h"
#include "DsEditView.h"
#include "operator/DsOperator.h"
#include "util/DsDebug.h"
#include "util/DsUtil.h"

void DsEditState::onEnter(DsEditState* )
{
}

void DsEditState::onExit(DsEditState* )
{
}
void DsEditState::mouseMoveEvent(QMouseEvent* )
{
}
void DsEditState::mousePressEvent(QMouseEvent* )
{
}
void DsEditState::mouseReleaseEvent(QMouseEvent* )
{
}
void DsEditState::wheelEvent(QMouseEvent* )
{
}
void DsEditState::keyPressEvent(QKeyEvent* )
{
}
void DsEditState::keyReleaseEvent(QKeyEvent* )
{

}
void DsEditState::enterEvent(QEvent* event)
{
}
void DsEditState::leaveEvent(QEvent* event)
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
                DsDebug<<"hit:"<<(*iter)->getID().c_str()<<endl;
                DsOperator::data()->setCurFrameImage((*iter)->getID());
                m_editView->changeToState(&m_editView->m_stateSelect);
                return;
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
DsEditStateSelect::DsEditStateSelect()
{
}

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
                DsDebug<<"hit:"<<(*iter)->getID().c_str()<<endl;
                DsOperator::data()->setCurFrameImage((*iter)->getID());
				return;
			}
		}
    }
    DsOperator::data()->dropCurFrameImage();

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
    else if(event->key()==Qt::Key_M)
    {
        m_editView->changeToState(&m_editView->m_stateMoveOffset);
    }
    else if(event->key()==Qt::Key_T)
    {
        m_editView->changeToState(&m_editView->m_stateTextureArea);
    }
    else if(event->key()==Qt::Key_Delete)
    {
        DsOperator::data()->removeCurFrameImage();

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
            m_editView->drawFrameImageBorder(image);
            m_editView->drawFrameImageCenter(image);
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
    DsFrame* frame=data->getCurFrame();
    if(frame==NULL)
    {
        return ;
    }
    assert(frame->getType()==DsFrame::FRAME_TWEEN);

    DsTweenFrame* cur_frame=(DsTweenFrame*)frame;
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
    dx/=m_editView->m_scale;
    dy/=m_editView->m_scale;

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
        DsOperator::data()->setCurFrameImagePos(x,y);
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

            DsFrameImage* temp=cur_frameImg->clone();
            float x,y;
            x=temp->getPosX();
            y=temp->getPosY();

            if(m_direction==DsEditState::DIRECTION_X)
            {
                temp->setPos(x+m_movex,y);
            }
            else if(m_direction==DsEditState::DIRECTION_Y)
            {
                temp->setPos(x,y+m_movey);
            }
            else
            {
                temp->setPos(x+m_movex,y+m_movey);
            }

            m_editView->drawFrameImage(temp);
            m_editView->drawFrameImageBorder(temp);
            m_editView->drawFrameImageCenter(temp);

            x=temp->getPosX();
            y=temp->getPosY();

            if(m_direction==DsEditState::DIRECTION_X)
            {

                m_editView->setLineColor(0.0,0.0,1.0);
                m_editView->drawLine(-100000,y,100000,y);
            }
            else if(m_direction==DsEditState::DIRECTION_Y)
            {
                m_editView->setLineColor(0.0,0.0,1.0);
                m_editView->drawLine(x,100000,x,-100000);
            }

            delete temp;
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
        DsOperator::data()->setCurFrameImageScale(sx,sy);
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
            DsFrameImage* temp=cur_frameImg->clone();
            float scale=getScale();
            glPushMatrix();
            float x,y,sx,sy,angle;

            x=temp->getPosX();
            y=temp->getPosY();
            sx=temp->getScaleX();
            sy=temp->getScaleY();

            if(m_direction==DsEditState::DIRECTION_X)
            {
                temp->setScale(sx*scale,sy);
            }
            else if(m_direction==DsEditState::DIRECTION_Y)
            {
                temp->setScale(sx,scale*sy);
            }
            else
            {
                temp->setScale(sx*scale,sy*scale);
            }

            m_editView->drawFrameImage(temp);
            m_editView->drawFrameImageBorder(temp);
            m_editView->drawFrameImageCenter(temp);

            glPushMatrix();
            m_editView->setFrameImageTransform(temp);

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
            glPopMatrix();

            delete temp;
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
        DsOperator::data()->setCurFrameImageAngle(g+m_angle);
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
            DsFrameImage* temp=cur_frameImg->clone();
            float angle;
            angle=temp->getAngle();
            angle+=m_angle;
            temp->setAngle(angle);
            m_editView->drawFrameImage(temp);
            m_editView->drawFrameImageBorder(temp);
            m_editView->drawFrameImageCenter(temp);
            delete temp;
        }
        else
        {
            m_editView->drawFrameImage(image);
        }

    }
}



DsEditStateAddImage::DsEditStateAddImage()
{
    m_image=NULL;
    m_draw=false;
}


void DsEditStateAddImage::onEnter(DsEditState* )
{
    m_draw=false;
}

void DsEditStateAddImage::mouseMoveEvent(QMouseEvent* event)
{
    float x=event->x();
    float y=event->y();

    m_editView->transformToRealCoord(&x,&y);
    m_image->setPos(x,y);
}

void  DsEditStateAddImage::draw()
{

    DsData* data=DsData::shareData();
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
    assert(cur_frame);

    int image_nu=cur_frame->getFrameImageNu();
    for(int i=image_nu-1;i>=0;i--)
    {
        DsFrameImage* image=cur_frame->getFrameImage(i);
        assert(image);
        m_editView->drawFrameImage(image);
    }

    if(m_draw)
    {
        m_editView->drawFrameImage(m_image);
    }

}

void DsEditStateAddImage::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        DsOperator::data()->addFrameImage(m_image);
        DsOperator::data()->setCurFrameImage(m_image->getID());
        m_editView->toDefaultState();

    }
    else if(event->buttons()&Qt::RightButton)
    {
        m_editView->toDefaultState();
    }
}

void DsEditStateAddImage::keyPressEvent(QKeyEvent* event)
{
    DsDebug<<"KeyPress"<<endl;
    if(event->key()==Qt::Key_Escape)
    {
        m_editView->toDefaultState();
    }
}


void DsEditStateAddImage::enterEvent(QEvent* )
{
    m_draw=true;
    m_editView->setFocus();
}

void DsEditStateAddImage::leaveEvent(QEvent* )
{
    m_draw=false;
}


DsEditStateMoveOffset::DsEditStateMoveOffset()
{
    m_movex=0;
    m_movey=0;
}

void DsEditStateMoveOffset::onEnter(DsEditState* prev)
{
    m_movex=0;
    m_movey=0;
}

void DsEditStateMoveOffset::mouseMoveEvent(QMouseEvent* event)
{
    QPoint last_pos=m_editView->m_lastpos;
    float dx=event->x()-last_pos.x();
    float dy=event->y()-last_pos.y();
    dx/=m_editView->m_scale;
    dy/=m_editView->m_scale;

    m_movex+=dx;
    m_movey+=-dy;
}

void DsEditStateMoveOffset::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        DsData* data=DsData::shareData();
        DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
        assert(((DsFrame*)cur_frame)->getType()==DsFrame::FRAME_KEY);

        DsFrameImage* cur_frameImg=data->getCurFrameImage();
        assert(cur_frameImg);
        float x=cur_frameImg->getOffsetX();
        float y=cur_frameImg->getOffsetY();

        cur_frameImg->transformVertexW(&x,&y);
        x+=m_movex;
        y+=m_movey;
        cur_frameImg->transformVertexL(&x,&y);


        DsOperator::data()->setCurFrameImageOffset(x,y);
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
    else if(event->buttons()&Qt::RightButton)
    {
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
}

void DsEditStateMoveOffset::draw()
{
    DsData* data=DsData::shareData();
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
    assert(((DsFrame*)cur_frame)->getType()==DsFrame::FRAME_KEY);

    DsFrameImage* cur_frameImg=data->getCurFrameImage();
    assert(cur_frameImg);

    int image_nu=cur_frame->getFrameImageNu();

    for(int i=image_nu-1;i>=0;i--)
    {
        DsFrameImage* image=cur_frame->getFrameImage(i);

        if(image==cur_frameImg)
        {

            DsFrameImage* temp=cur_frameImg->clone();
            float x,y;
            x=temp->getOffsetX();
            y=temp->getOffsetY();

            temp->transformVertexW(&x,&y);
            x+=m_movex;
            y+=m_movey;
            temp->transformVertexL(&x,&y);

            temp->setOffset(x,y);

            m_editView->drawFrameImage(temp);
            m_editView->drawFrameImageBorder(temp);
            m_editView->drawFrameImageCenter(temp);
            delete temp;
        }
        else
        {
            m_editView->drawFrameImage(image);
        }

    }
}


DsEditStateTextureArea::DsEditStateTextureArea()
{
    m_movevx0=0;
    m_movevy0=0;
    m_movevx1=0;
    m_movevy1=0;
    m_direction=DsEditState::DIRECTION_BOTH;
}

void DsEditStateTextureArea::onEnter(DsEditState* prev)
{
    m_movevx0=0;
    m_movevy0=0;
    m_movevx1=0;
    m_movevy1=0;
    m_direction=DsEditState::DIRECTION_BOTH;
}

void DsEditStateTextureArea::mouseMoveEvent(QMouseEvent* event)
{
    QPoint last_pos=m_editView->m_lastpos;
    float dx=event->x()-last_pos.x();
    float dy=event->y()-last_pos.y();
    dx/=m_editView->m_scale;
    dy/=m_editView->m_scale;

    if(m_direction==DsEditState::DIRECTION_A)
    {
        m_movevx0+=dx;
        m_movevy0+=-dy;
    }
    else if(m_direction==DsEditState::DIRECTION_B)
    {
        m_movevx1+=dx;
        m_movevy1+=-dy;
    }
    else if(m_direction=DsEditState::DIRECTION_BOTH)
    {
        m_movevx0+=dx;
        m_movevy0+=-dy;
        m_movevx1+=dx;
        m_movevy1+=-dy;
    }
}

void DsEditStateTextureArea::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        DsData* data=DsData::shareData();
        DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
        assert(((DsFrame*)cur_frame)->getType()==DsFrame::FRAME_KEY);

        DsFrameImage* cur_frameImg=data->getCurFrameImage();
        assert(cur_frameImg);
        float cx0,cy0,cx1,cy1;
        cur_frameImg->getTextureArea(&cx0,&cy0,&cx1,&cy1);
        float mvx0=m_movevx0,mvy0=m_movevy0,mvx1=m_movevx1,mvy1=m_movevy1;

        cur_frameImg->transformVertexVL(&mvx0,&mvy0);
        cur_frameImg->transformVertexVL(&mvx1,&mvy1);

        mvx0/=cur_frameImg->getWidth();
        mvx1/=cur_frameImg->getWidth();
        mvy0/=cur_frameImg->getHeight();
        mvy1/=cur_frameImg->getHeight();

        cx0+=mvx0;
        cx1+=mvx1;
        cy0+=mvy0;
        cy1+=mvy1;
        cx0=DsUtil::clamp(cx0,0,1);
        cx1=DsUtil::clamp(cx1,0,1);
        cy0=DsUtil::clamp(cy0,0,1);
        cy1=DsUtil::clamp(cy1,0,1);

        cur_frameImg->setTextureArea(cx0,cy0,cx1,cy1);

        m_editView->changeToState(&m_editView->m_stateSelect);
    }
    else if(event->buttons()&Qt::RightButton)
    {
        m_editView->changeToState(&m_editView->m_stateSelect);
    }
}

void DsEditStateTextureArea::keyPressEvent(QKeyEvent* event)
{
    if(m_direction==DsEditState::DIRECTION_BOTH)
    {
        if(event->key()==Qt::Key_A)
        {
            m_direction=DsEditState::DIRECTION_A;
        }
        else if(event->key()==Qt::Key_B)
        {
            m_direction=DsEditState::DIRECTION_B;
        }
        else if(event->key()==Qt::Key_Escape)
        {
            m_editView->changeToState(&m_editView->m_stateSelect);
        }
    }
    else if(m_direction==DsEditState::DIRECTION_A)
    {
        if(event->key()==Qt::Key_B)
        {
            m_direction=DsEditState::DIRECTION_B;
        }
        else if(event->key()==Qt::Key_Escape)
        {
            m_direction=DsEditState::DIRECTION_BOTH;
        }
    }
    else if(m_direction==DsEditState::DIRECTION_B)
    {
        if(event->key()==Qt::Key_A)
        {
            m_direction=DsEditState::DIRECTION_A;
        }
        else if(event->key()==Qt::Key_Escape)
        {
            m_direction=DsEditState::DIRECTION_BOTH;
        }
    }

}

void DsEditStateTextureArea::draw()
{
    DsData* data=DsData::shareData();
    DsKeyFrame* cur_frame=(DsKeyFrame*)data->getCurFrame();
    assert(((DsFrame*)cur_frame)->getType()==DsFrame::FRAME_KEY);

    DsFrameImage* cur_frameImg=data->getCurFrameImage();
    assert(cur_frameImg);

    int image_nu=cur_frame->getFrameImageNu();

    for(int i=image_nu-1;i>=0;i--)
    {
        DsFrameImage* image=cur_frame->getFrameImage(i);

        if(image==cur_frameImg)
        {

            DsFrameImage* temp=cur_frameImg->clone();

            float cx0,cy0,cx1,cy1;

            float fx0=m_movevx0,fy0=m_movevy0;
            float fx1=m_movevx1,fy1=m_movevy1;

            temp->getTextureArea(&cx0,&cy0,&cx1,&cy1);
            temp->setTextureArea(0,0,1,1);
            m_editView->drawFrameImageWithGray(temp);

            temp->transformVertexVL(&fx0,&fy0);
            temp->transformVertexVL(&fx1,&fy1);

            fx0=fx0/temp->getWidth();
            fy0=fy0/temp->getHeight();
            fx1=fx1/temp->getWidth();
            fy1=fy1/temp->getHeight();

            cx0+=fx0;
            cy0+=fy0;
            cx1+=fx1;
            cy1+=fy1;

            cx0=DsUtil::clamp(cx0,0,1);
            cy0=DsUtil::clamp(cy0,0,1);
            cx1=DsUtil::clamp(cx1,0,1);
            cy1=DsUtil::clamp(cy1,0,1);

            temp->setTextureArea(cx0,cy0,cx1,cy1);
            m_editView->drawFrameImage(temp);
            m_editView->drawFrameImageBorder(temp);
            m_editView->drawFrameImageCenter(temp);
            delete temp;
        }
        else
        {
            m_editView->drawFrameImage(image);
        }

    }
}



































