#include <QtGui>
#include <QtOpenGL>
#include "DsEditView.h"
#include <QTextStream>

DsEditView::DsEditView(QWidget* parent)
    :QGLWidget(parent)
{
    m_space_down=false;
    m_lastpos=QPoint(0,0);
	m_tx=0;
	m_ty=0;
	m_sx=1;
	m_sy=1;
}

void DsEditView::initializeGL()
{
	//glEnable(GL_DEPTH_TEST)
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
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
void DsEditView::draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_LINES);
	{
		glColor3f(1.0,0.0,1.0);
        glVertex3f(50,50,0);
        glVertex3f(-50,-50,0);
	}
	glEnd();
}

void DsEditView::paintGL()
{
    draw();
}

void DsEditView::mousePressEvent(QMouseEvent* event)
{
	m_lastpos=event->pos();
}

void DsEditView::mouseMoveEvent(QMouseEvent* event)
{
	float dx=event->x()-m_lastpos.x();
    float dy=event->y()-m_lastpos.y();

	if(event->buttons()&Qt::LeftButton)
    {
        QTextStream out(stdout) ;
        printf("left button\n");
        if(m_space_down)
        {
            printf("tx=%f,ty=%d\n",m_tx,m_ty);
            m_tx+=dx;
            m_ty+=dy;
        }
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

void DsEditView::keyPressEvent(QKeyEvent* event)
{

    printf("keypress\n");
    switch(event->key())
    {
    case Qt::Key_Space:
        printf("keypress space\n");
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


















