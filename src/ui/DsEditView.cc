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


	/* axis and grid */
    m_showAxis=true;
    m_showGrid=false;
	m_gridWidth=32;
	m_gridHeight=32;

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
    m_stateMoveOffset.setEditView(this);
    m_curState=&m_stateIdel;
    toDefaultState();

}
void DsEditView::toDefaultState()
{
	DsData* data=DsData::shareData();
    DsFrame* frame=data->getCurFrame();
    DsFrameImage* image=data->getCurFrameImage();

	if(frame==NULL)
    {
        changeToState(&m_stateNotEdit);
	}
	else 
	{
		if(frame->getType()==DsFrame::FRAME_KEY)
        {
            if(image)
            {
                changeToState(&m_stateSelect);
            }
            else
            {
                changeToState(&m_stateIdel);
            }
		}
		else 
        {
            changeToState(&m_stateNotEdit);
		}
	}
}

void DsEditView::slotCurAnimationChange()
{
    toDefaultState();
}
void DsEditView::slotCurFrameChange()
{
    toDefaultState();
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
    y=wsize.height()/2-y;

    float rx=(x-m_tx)/scale;
    float ry=(y-m_ty)/scale;

    detal=event->delta()>0?1.1f:0.9f;
    m_scale*=detal;

    m_tx=x-rx*m_scale;
    m_ty=y-ry*m_scale;
    update();
}

void DsEditView::enterEvent(QEvent* event)
{
    m_curState->enterEvent(event);
    update();
}
void DsEditView::leaveEvent(QEvent* event)
{
    m_curState->leaveEvent(event);
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

void DsEditView::zoomIn()
{
    m_scale*=1.1f;
    update();
}
void DsEditView::zoomOut()
{
    m_scale*=0.9f;
    update();
}
void DsEditView::resetZoomTranslate()
{
    m_tx=0;
    m_ty=0;
    m_scale=1.0;
    update();
}


void DsEditView::setShowAxis(bool enable)
{
    m_showAxis=enable;
    update();
}
void DsEditView::setShowGrid(bool enable)
{
    m_showGrid=enable;
    update();
}

void DsEditView::draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* move editor area */
    glTranslatef(m_tx,m_ty,0);
    /* zoom editor area */
    glScalef(m_scale,m_scale,1);




    /* draw  grid */
    if(m_showGrid)
    {
        drawGrid();
    }

    /* draw Axis */
    if(m_showAxis)
    {
        drawAxis();
    }


    /* draw to clientarea */
    m_curState->draw();

}

void DsEditView::drawAxis()
{
    glDisable(GL_TEXTURE_2D);

    setLineColor(0.0,0.0,1.0);
    drawLine(-100000,0,100000,0);
    setLineColor(0.0,1.0,0.0);
    drawLine(0,-100000,0,100000);
}
void DsEditView::drawGrid()
{
	QSize wsize=size();
	float x0,y0,x1,y1;
	x0=0;
	y0=0;
	x1=wsize.width();
	y1=wsize.height();

	transformToRealCoord(&x0,&y0);
	transformToRealCoord(&x1,&y1);

	int vline_start=x0/m_gridWidth;
    int vline_end=x1/m_gridWidth+1;

    int hline_start=y0/m_gridHeight;
    int hline_end=y1/m_gridHeight+1;

    if(hline_start>hline_end)
    {
        int temp=hline_start;
        hline_start=hline_end;
        hline_end=temp;
    }

    DsDebug<<" x0:"<<vline_start<<" y0:"<<vline_end<<" x1:"<<hline_start<<" y1"<<hline_end<<endl;

    setLineColor(0.8f,0.8f,0.8f);
	for(int i=vline_start;i<=vline_end;i++)
	{
		drawLine(i*m_gridWidth,-10000,i*m_gridWidth,10000);
    }
    for(int i=hline_start;i<=hline_end;i++)
    {
        drawLine(-10000,i*m_gridHeight,10000,i*m_gridHeight);
    }
}
void DsEditView::drawFrameImage(DsFrameImage* image)
{
    glPushMatrix();
    setFrameImageTransform(image);
	rawDrawFrameImage(image);
    glPopMatrix();
}

void DsEditView::setFrameImageTransform(DsFrameImage* image)
{
    float x,y,sx,sy,angle;

    x=image->getPosX();
    y=image->getPosY();

    sx=image->getScaleX();
    sy=image->getScaleY();

    angle=image->getAngle();


    glTranslatef(x,y,0);
    glRotatef(angle,0,0,1);
    glScalef(sx,sy,1);
}


void DsEditView::drawFrameImageBorder(DsFrameImage* image)
{
    float vx0,vy0,vx1,vy1;
    glPushMatrix();
    setFrameImageTransform(image);
    image->getVertex(&vx0,&vy0,&vx1,&vy1);
    setLineColor(1.0,0.0,0.0);
    drawLine(vx0,vy0,vx1,vy0);
    drawLine(vx1,vy0,vx1,vy1);
    drawLine(vx1,vy1,vx0,vy1);
    drawLine(vx0,vy1,vx0,vy0);
    glPopMatrix();
}
void DsEditView::drawFrameImageCenter(DsFrameImage* image)
{
    float x,y;
    x=image->getPosX();
    y=image->getPosY();
    setPointColor(1.0,0.0,0.0,1.0);
    drawPoint(x,y,5.0);
}


void DsEditView::rawDrawFrameImage(DsFrameImage* image)
{
    float width=image->getWidth();
    float height=image->getHeight();
    float cx0,cy0,cx1,cy1;
    float vx0,vy0,vx1,vy1;
    float alpha;
    float fx,fy;

    image->getTextureArea(&cx0,&cy0,&cx1,&cy1);
    image->getVertex(&vx0,&vy0,&vx1,&vy1);

    DsImage* ds_img=image->getImage();
    if(ds_img->texture==0)
    {
        ds_img->texture=bindTexture(*ds_img->image);
    }
    alpha=image->getAlpha();


    glColor4f(1.0,1.0,1.0,alpha);
    glBindTexture(GL_TEXTURE_2D,ds_img->texture);

    float vertex[8]=
    {
        vx0,vy0,
        vx1,vy0,
        vx1,vy1,
        vx0,vy1
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
}

void DsEditView::drawPoint(float x,float y,float size)
{
    glPointSize(size);
    glColor4f(m_pr,m_pg,m_pb,m_pa);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
}

void DsEditView::setPointColor(float r,float g,float b,float a)
{
    m_pr=r;
    m_pg=g;
    m_pb=b;
    m_pa=a;
}
void DsEditView::setLineColor(float r,float g,float b,float a)
{
    m_lr=r;
    m_lg=g;
    m_lb=b;
    m_la=a;
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
void DsEditView::drawDashLine(float x0,float y0,float x1,float y1,float width)
{
    glLineStipple(1,0x66666666);
    glLineWidth(width);
    glEnable(GL_LINE_STIPPLE);

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
    glDisable(GL_LINE_STIPPLE);
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
void DsEditView::transformToWidgetCoord(float* x,float *y)
{
    float rx=*x;
    float ry=*y;
    QSize  wsize=size();
    rx=rx*m_scale+m_tx;
    ry=ry*m_scale+m_ty;
    rx=rx+wsize.width()/2;
    ry=wsize.height()/2-ry;

    *x=rx;
    *y=ry;
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

void DsEditView::slotAddFrameImage(const std::string& path,const std::string& name)
{
    if(m_curState==&m_stateNotEdit)
    {
        return;
    }

    std::string full_path=path+name;

    DsFrameImage* frame_image=DsFrameImage::create(full_path);

    m_stateAddImage.setFrameImage(frame_image);
    changeToState(&m_stateAddImage);
}


























