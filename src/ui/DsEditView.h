#ifndef _DS_EDIT_VIEW_H_
#define _DS_EDIT_VIEW_H_

#include <QGLWidget>

#include "model/DsData.h"
#include "model/DsFrame.h"
#include "model/DsSprite.h"
#include "model/DsProject.h"
#include "model/DsAnimation.h"

class DsEditView:public QGLWidget
{
	Q_OBJECT
	public:
		enum
		{
			ST_IDEL,
			ST_ADD_IMAGE,
			ST_SELECT,
			ST_SCALE,
			ST_MOVE,
			ST_ROTATE,
		};

	public:	
        DsEditView(QWidget* parent);
        void draw();
    public:
        void setScale(float s);
        float getScale(){return m_scale;}

        void setTranslate(float x,float y);
        float getTranslateX(){return m_tx;}
        float getTranslateY(){return m_ty;}

        void setShowAxis(bool enable);

	public:
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
        void focusInEvent(QFocusEvent* event);
        void focusOutEvent(QFocusEvent* event);
        void wheelEvent(QWheelEvent* event);

	public:
		void handleLeftButtonDown();


    protected:
        virtual void initializeGL();
        virtual void resizeGL(int width,int height);
        virtual void paintGL();

		
        void drawAxis();
		void drawGrid();
		void drawAnimation();
        void drawFrameImage(DsFrameImage* image);
		void drawFrameImageDecorate(DsFrameImage* image);
		void setLineColor(float r,float g,float b,float a=1.0);
		void drawLine(float x0,float y0,float x1,float y1,float width=1.0f);

	private:
        QPoint m_lastpos;
        bool m_space_down;
        float m_tx,m_ty;
        float m_scale;

        bool m_showAxis;
		bool m_showGrid;
		bool m_imageLocalCoord;

		/* gl infomation */
		float m_r,m_g,m_b,m_a;

		/* state info*/

		bool m_state;

		/* st_add_image */
		DsImage* m_addImage;

		/* st_scale */
		float mst_sx,mst_sy;






};

#endif /*_DS_EDIT_VIEW_H_*/













