#include <QtGui>
#include <QtOpenGL>
#include "DsEditView.h"
#include <QTextStream>
#include <vector>
#include "util/DsDebug.h"




DsEditView::DsEditView(QWidget* parent)
    :QGLWidget(parent)
{
    m_spaceDown=false;
    m_lastpos=QPoint(0,0);
	m_tx=0;
    m_ty=0;
    m_scale=1;
    m_r=1;
    m_g=1;
    m_b=1;
    m_a=1;

    /*  space down */
    m_spaceDown=false;
    m_sDPrevCursor=Qt::ArrowCursor;

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
	initState();
}
void DsEditView::initState()
{
	m_stateNotEdit.setEditView(this);
    m_stateIdel.setEditView(this);
    m_stateAddImage.setEditView(this);
    m_stateTranslate.setEditView(this);
    m_stateScale.setEditView(this);
    m_stateRotate.setEditView(this);
    m_stateSelect.setEditView(this);
    m_statePlay.setEditView(this);
    m_stateMoveCoord.setEditView(this);

	DsData* data=DsData::shareData();
	DsFrame* frame=data->getCurFrame();
	if(frame==NULL)
	{
		m_curState=&m_stateIdel;
	}
	else 
	{
		if(frame->getType()==DsFrame::FRAME_KEY)
		{
			m_curState=&m_stateIdel;
		}
		else 
		{
			m_curState=&m_stateNotEdit;
		}
	}
}
void DsEditView::slotCurFrameChange()
{
    DsData* data=DsData::shareData();
    DsFrame* frame=data->getCurFrame();
    if(frame==NULL)
	{
        changeToState(&m_stateIdel);
	}
	else 
	{
		if(frame->getType()==DsFrame::FRAME_KEY)
		{
            changeToState(&m_stateIdel);
		}
		else 
		{
            changeToState(&m_stateNotEdit);
		}
	}
}

void DsEditView::initializeGL()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glBlen
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClearColor(1.0,1.0,1.0,1.0);
}

void DsEditView::resizeGL(int width,int height)
{
	glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2,width/2,-height/2,height/2,0,100);
    glMatrixMode(GL_MODELVIEW);
    update();
}

void DsEditView::paintGL()
{
    draw();
}


void DsEditView::mousePressEvent(QMouseEvent* event)
{
    setFocus();
    if(m_spaceDown)
    {
        m_lastpos=event->pos();
        return;
    }
    m_curState->mousePressEvent(event);
    m_lastpos=event->pos();
    update();
}

void DsEditView::mouseMoveEvent(QMouseEvent* event)
{
    float dx=event->x()-m_lastpos.x();
    float dy=-(event->y()-m_lastpos.y());


    if(event->buttons()&Qt::LeftButton)
    {
        if(m_spaceDown)
        {
            setTranslate(m_tx+dx,m_ty+dy);
            m_lastpos=event->pos();
            return ;
        }
    }

    m_curState->mouseMoveEvent(event);
    m_lastpos=event->pos();
    update();
}

void DsEditView::mouseReleaseEvent(QMouseEvent* event)
{
    m_curState->mouseReleaseEvent(event);
    m_lastpos=event->pos();
    update();
}
void DsEditView::wheelEvent(QWheelEvent* event)
{
    float detal;

    float scale=m_scale;
    float x=event->x();
    float y=event->y();

    QSize wsize=size();
    x=x-wsize.width()/2;
    y=y-wsize.height()/2;

    float rx=(x-m_tx)/scale;
    float ry=(y-m_ty)/scale;

    detal=m_scale>1.0f?0.2f:0.1f;
    m_scale+=(event->delta()/120.0f)*detal;
    if(m_scale<0.1)
    {
        m_scale=0.1f;
    }

    m_tx=x-rx*m_scale;
    m_ty=y-ry*m_scale;
    update();
}

void DsEditView::keyPressEvent(QKeyEvent* event)
{

    switch(event->key())
    {
    case Qt::Key_Space:
        m_spaceDown=true;
        m_sDPrevCursor=cursor();
        setCursor(Qt::ClosedHandCursor);
        break;
    default:
        break;
    }
    m_curState->keyPressEvent(event);
    update();
}

void DsEditView::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Space:
        m_spaceDown=false;
        setCursor(m_sDPrevCursor);
        m_sDPrevCursor=Qt::ArrowCursor;
        break;
    default:
        break;
    }
    m_curState->keyReleaseEvent(event);
    update();
}

void DsEditView::focusInEvent(QFocusEvent* event)
{
    DsDebug<<"focus in"<<endl;
}
void DsEditView::focusOutEvent(QFocusEvent* event)
{
    DsDebug<<"foucs out"<<endl;
}

void DsEditView::setTranslate(float x,float y)
{
    m_tx=x;
    m_ty=y;
    update();
}
void DsEditView::setScale(float scale)
{
    m_scale=scale;
    update();
}

void DsEditView::setShowAxis(bool enable)
{
    m_showAxis=enable;
    update();
}

void DsEditView::draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* move editor area */
    glTranslatef(m_tx,m_ty,0);


    /* draw Axis */
    if(m_showAxis)
    {
        drawAxis();
    }


    /* zoom editor area */
    glScalef(m_scale,m_scale,1);

    /* draw  grid */
    if(m_showGrid)
    {
        drawGrid();
    }


    /* draw to clientarea */
    m_curState->draw();

}

void DsEditView::drawAxis()
{
    glDisable(GL_TEXTURE_2D);

    setLineColor(1.0,0.0,0.0);
    drawLine(-100000,0,100000,0);
    setLineColor(0.0,1.0,0.0);
    drawLine(0,-100000,0,100000);
}
void DsEditView::drawGrid()
{
    /*TODO*/
}
void DsEditView::drawFrameImage(DsFrameImage* image)
{
    glPushMatrix();
    float x,y,width,height,sx,sy,angle;
    float cx0,cy0,cx1,cy1;

    x=image->getPosX();
    y=image->getPosY();

    width=image->getWidth();
    height=image->getHeight();

    sx=image->getScaleX();
    sy=image->getScaleY();

    angle=image->getAngle();

    width*=sx;
    height*=sx;

    image->getTextureArea(&cx0,&cy0,&cx1,&cy1);


    glTranslatef(x,y,0);
    glRotatef(angle,0,0,1);


    DsImage* ds_img=image->getImage();
    if(ds_img->texture==0)
    {
        ds_img->texture=bindTexture(*ds_img->image);
    }

    /*
    out<<"wdith:"<<ds_img->image->width()<<" height:"<<ds_img->image->height()<<endl;

    out<<"DrawImage:"<<image->getName().c_str()<<" x:"<<x<<" y:"<<y<<" width:"<<width<<" height:"<<height;
    out<<" sx:"<<sx<<" sy:"<<sy;
    out<<" tex:"<<ds_img->texture<<" tx0:"<<cx0<<" cy0:"<<cy0<<" cx1:"<<cx1<<" cy1:"<<cy1<<endl;
    */

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,ds_img->texture);

    float vertex[8]=
    {
        -width/2,-height/2,
        width/2,-height/2,
        width/2,height/2,
        -width/2,height/2
    };
    float texcoord[8]=
    {
        cx0,cy0,
        cx1,cy0,
        cx1,cy1,
        cx0,cy1
    };
    glVertexPointer(2,GL_FLOAT,0,vertex);
    glTexCoordPointer(2,GL_FLOAT,0,texcoord);

    glDrawArrays(GL_QUADS,0,4);
    glPopMatrix();
}
void DsEditView::setLineColor(float r,float g,float b,float a)
{
    m_r=r;
    m_g=g;
    m_b=b;
    m_a=a;
}

void DsEditView::drawLine(float x0,float y0,float x1,float y1,float width)
{
    glLineWidth(width);

    glColor4f(m_r,m_g,m_b,m_a);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    float vertex[4]=
    {
        x0,y0,
        x1,y1
    };

    glVertexPointer(2,GL_FLOAT,0,vertex);
    glDrawArrays(GL_LINES,0,2);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}	

void DsEditView::drawFrameImageDecorate(DsFrameImage* image)
{
}




void DsEditView::transformToRealCoord(float* x,float* y)
{
    float rx=*x;
    float ry=*y;

    QSize wsize=size();

    rx=rx-wsize.width()/2;
    ry=wsize.height()/2-ry;


    *x=(rx-m_tx)/m_scale;
    *y=(ry-m_ty)/m_scale;
}

void DsEditView::changeToState(DsEditState* target)
{
    if(m_curState==target)
    {
        return;
    }
    m_curState->onExit(target);
    target->onEnter(m_curState);
    m_curState=target;
}






















