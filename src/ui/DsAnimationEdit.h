#ifndef _DS_ANIMATION_EDIT_H_
#define _DS_ANIMATION_EDIT_H_

#include <QWidget>
#include <QMenu>

class DsAnimationEdit:public QWidget
{
	Q_OBJECT
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
		void drawCurSelectFrame(QPainter& painter);
		void createPopupMenu();

		public slots:
			void slotInsertKeyFrame();
		void slotInsertEmptyKeyFrame();
		void slotRemoveFrame();
		void slotCreateTween();
		void slotRemoveTween();
		void slotTweenToKeyFrame();
	private:
		QPoint m_lastpos;
		int m_move;
		int m_ruler_unit;
		int m_ruler_height;
		int m_frame_height;

		/* menu */
		QMenu* m_menu;
		QAction* ma_insertKeyFrame;
		QAction* ma_insertEmptyKeyFrame;
		QAction* ma_removeFrame;
		QAction* ma_createTween;
		QAction* ma_removeTween;
		QAction* ma_tweenToKeyFrame;
};
#endif /*_DS_ANIMATION_H_*/

