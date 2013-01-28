#ifndef _DS_ANIMATION_EDIT_H_
#define _DS_ANIMATION_EDIT_H_

#include <QWidget>

class DsAnimationEdit:public QWidget
{
	public:
		DsAnimationEdit(QWidget* parent);
	public:
        virtual void paintEvent(QPaintEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
		virtual void mousePressEvent(QMouseEvent* event);
	protected:
		void drawRuler(QPainter& painter);
		void drawFrame(QPainter& painter);
		void drawKeyFrames(QPainter& painter);
		void drawSelectFrame(QPainter& painter);

	private:
		QPoint m_lastpos;
		int m_move;
		int m_ruler_unit;
		int m_ruler_height;
};
#endif /*_DS_ANIMATION_H_*/

