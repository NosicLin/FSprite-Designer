#include <QtGui>
#include <QtOpenGL>
#include "DsEditView.h"
#include <QTextStream>
#include <vector>


QTextStream out(stdout) ;

DsEditView::DsEditView(QWidget* parent)
    :QGLWidget(parent)
{
    m_space_down=false;
    m_lastpos=QPoint(0,0);
	m_tx=0;
    m_ty=0;
    m_scale=1;
    m_r=1;
    m_g=1;
    m_b=1;
    m_a=1;
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
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
}

void DsEditView::paintGL()
{
    draw();
}


void DsEditView::mousePressEvent(QMouseEvent* event)
{
    setFocus();
	m_lastpos=event->pos();
}

void DsEditView::mouseMoveEvent(QMouseEvent* event)
{
    float dx=event->x()-m_lastpos.x();
    float dy=event->y()-m_lastpos.y();


    if(event->buttons()&Qt::LeftButton)
    {
        if(m_space_down)
        {
            setTranslate(m_tx+dx,m_ty+dy);
        }
     //   handleLeftButtonDown();

    }
    else if(event->buttons()&Qt::RightButton)
    {
    }
    else if(event->buttons()&Qt::MiddleButton)
    {
    }
    m_lastpos=event->pos();
}

void DsEditView::mouseReleaseEvent(QMouseEvent* event)
{


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
    draw();
}

void DsEditView::keyPressEvent(QKeyEvent* event)
{

    switch(event->key())
    {
    case Qt::Key_Space:
        m_space_down=true;
        break;
    default:
        break;
    }
}

void DsEditView::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Space:
        m_space_down=false;
        break;
    default:
        break;
    }
}

void DsEditView::focusInEvent(QFocusEvent* event)
{
    out<<"focus in"<<endl;
}
void DsEditView::focusOutEvent(QFocusEvent* event)
{
    out<<"foucs out"<<endl;
}

void DsEditView::setTranslate(float x,float y)
{
    m_tx=x;
    m_ty=y;
    draw();
}
void DsEditView::setScale(float scale)
{
    m_scale=scale;
    draw();
}

void DsEditView::setShowAxis(bool enable)
{
    m_showAxis=enable;
    draw();
}


void DsEditView::drawAnimation()
{
    DsData* data=DsData::shareData();
    DsAnimation* animation=data->getCurAnimation();
    if(animation==NULL)
    {
        return;
    }

    DsFrame* frame=data->getCurFrame();
    if(frame==NULL)
    {
        return;
    }

    std::vector<DsFrameImage*> images;
    DsFrame::Iterator iter=frame->begin();

    DsFrameImage* select_image=data->getCurFrameImage();


    for(;iter!=frame->end();++iter)
    {
        images.push_back(*iter);
    }

    for(int i=images.size()-1;i>=0;i--)
    {
        DsFrameImage* cur_image=images[i];
        if(cur_image==select_image)
        {
            drawFrameImageDecorate(cur_image);
        }
		else 
		{
			drawFrameImage(cur_image);
		}
    }




}

void DsEditView::draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* move editor area */
    glTranslatef(m_tx,-m_ty,0);


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


    /* draw animation */
    drawAnimation();


	setLineColor(0.0,0.0,1.0);
	drawLine(100,100,-100,-100);

    swapBuffers();
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
	glRotatef(0,0,1,angle);


    DsImage* ds_img=image->getImage();
    if(ds_img->texture==0)
    {
        ds_img->texture=bindTexture(*ds_img->image);
    }

    out<<"wdith:"<<ds_img->image->width()<<" height:"<<ds_img->image->height()<<endl;

    out<<"DrawImage:"<<image->getName().c_str()<<" x:"<<x<<" y:"<<y<<" width:"<<width<<" height:"<<height;
    out<<" sx:"<<sx<<" sy:"<<sy;
    out<<" tex:"<<ds_img->texture<<" tx0:"<<cx0<<" cy0:"<<cy0<<" cx1:"<<cx1<<" cy1:"<<cy1<<endl;

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

void handleLeftButtonDown()
{
}



























