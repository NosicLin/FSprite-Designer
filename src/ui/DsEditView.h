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

        void zoomIn();
        void zoomOut();
        void resetZoomTranslate();

        void setShowAxis(bool enable);
        void setShowGrid(bool enable);

		void setGridSize(int width,int height);
		int getGridHeight();
		int getGridWidth();

        void changeToState(DsEditState* state);
        void toDefaultState();

	public:
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
        void focusInEvent(QFocusEvent* event);
        void focusOutEvent(QFocusEvent* event);
        void wheelEvent(QWheelEvent* event);
        void enterEvent(QEvent* event);
        void leaveEvent(QEvent* event);

	public slots:
        void slotCurFrameChange();
        void slotCurAnimationChange();
        void slotAddFrameImage(const std::string& path,const std::string& name);

    protected:
		void initState();
        virtual void initializeGL();
        virtual void resizeGL(int width,int height);
        virtual void paintGL();
		
        void drawAxis();
		void drawGrid();

        void drawFrameImage(DsFrameImage* image);
        void drawFrameImageWithColor(DsFrameImage* image,float r,float g,float b,float a);
        void drawFrameImageWithGray(DsFrameImage* image,float gray=1.0);
        void rawDrawFrameImage(DsFrameImage* image,float r=1.0,float g=1.0,float b=1.0,float a=1.0);
        void setFrameImageTransform(DsFrameImage* image);
        void drawFrameImageBorder(DsFrameImage* image);
        void drawFrameImageCenter(DsFrameImage* image);

        void drawFrameImageDecorate(DsFrameImage* image);

        void drawPoint(float x,float y,float size);
        void setPointColor(float r,float g,float b,float a=1.0);
		void setLineColor(float r,float g,float b,float a=1.0);
		void drawLine(float x0,float y0,float x1,float y1,float width=1.0f);
        void drawDashLine(float x0,float y0,float x1,float y1,float width=1.0f);

        void transformToRealCoord(float* x,float* y);
        void transformToWidgetCoord(float* x,float* y);

	private:
        QPoint m_lastpos;
        float m_tx,m_ty;
        float m_scale;

        bool m_showAxis;
		bool m_showGrid;
		int m_gridWidth;
		int m_gridHeight;

		bool m_imageLocalCoord;

		/* gl infomation */
        float m_lr,m_lg,m_lb,m_la;
        float m_pr,m_pg,m_pb,m_pa;

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
        DsEditStateMoveOffset m_stateMoveOffset;
        DsEditStateTextureArea m_stateTextureArea;


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
        friend class DsEditStateMoveOffset;
        friend class DsEditStateTextureArea;
};


#endif /*_DS_EDIT_VIEW_H_*/



















