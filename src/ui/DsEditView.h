#ifndef _DS_EDIT_VIEW_H_
#define _DS_EDIT_VIEW_H_

#include <QGLWidget>

class DsEditView:public QGLWidget
{
	Q_OBJECT
	public:	
        DsEditView(QWidget* parent);
        void draw();
	public:
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);

    protected:
        virtual void initializeGL();
        virtual void resizeGL(int width,int height);
        virtual void paintGL();
	private:
        QPoint m_lastpos;
        bool m_space_down;
		float m_tx,m_ty;
		float m_sx,m_sy;
};




#endif /*_DS_EDIT_VIEW_H_*/

