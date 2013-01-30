#ifndef _DS_EDIT_VIEW_H_
#define _DS_EDIT_VIEW_H_

#include <QGLWidget>
#include <QTextStream>

#include "model/DsData.h"
#include "model/DsFrame.h"
#include "model/DsSprite.h"
#include "model/DsProject.h"
#include "model/DsAnimation.h"

#include "DsEditState.h"



class DsEditView:public QGLWidget
{
	Q_OBJECT
    public:
        enum
        {
            DIRECTIION_X,
            DIRECTTION_Y,
            DIRECTION_BOTH
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
		void changeToState(DsEditState* state);

	public:
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
        void focusInEvent(QFocusEvent* event);
        void focusOutEvent(QFocusEvent* event);
        void wheelEvent(QWheelEvent* event);

	public slots:
		void slotCurFrameChange();


    protected:
		void initState();
        virtual void initializeGL();
        virtual void resizeGL(int width,int height);
        virtual void paintGL();

		
        void drawAxis();
		void drawGrid();
        void drawFrameImage(DsFrameImage* image);
		void drawFrameImageDecorate(DsFrameImage* image);
		void setLineColor(float r,float g,float b,float a=1.0);
		void drawLine(float x0,float y0,float x1,float y1,float width=1.0f);

		void transformToRealCoord(float* x,float* y);

	private:
        QPoint m_lastpos;
        float m_tx,m_ty;
        float m_scale;

        bool m_showAxis;
		bool m_showGrid;
		bool m_imageLocalCoord;

		/* gl infomation */
		float m_r,m_g,m_b,m_a;

		/* state information */
        DsEditState* m_curState;

        /* space move state */
        bool m_spaceDown;
        QCursor m_sDPrevCursor;


        /* all state */
        DsEditStateNotEdit m_stateNotEdit;
        DsEditStateIdel m_stateIdel;
		DsEditStateAddImage m_stateAddImage;
		DsEditStateTranslate m_stateTranslate;
		DsEditStateScale m_stateScale;
		DsEditStateRotate m_stateRotate;
		DsEditStateSelect m_stateSelect;
		DsEditStatePlay m_statePlay;
		DSEditStateMoveCoord m_stateMoveCoord;


	public:
		friend class DsEditState;
		friend class DsEditStateNotEdit;
		friend class DsEditStateIdel;
		friend class DsEditStateAddImage;
		friend class DsEditStateTranslate;
		friend class DsEditStateScale;
		friend class DsEditStateRotate;
		friend class DsEditStateSelect;
		friend class DsEditStatePlay;
		friend class DSEditStateMoveCoord;
};


#endif /*_DS_EDIT_VIEW_H_*/



















