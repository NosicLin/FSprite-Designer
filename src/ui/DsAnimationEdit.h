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
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void keyPressEvent(QKeyEvent* event);
	protected:
		void drawRuler(QPainter& painter);
		void drawFrame(QPainter& painter);
		void drawKeyFrames(QPainter& painter);
        void drawCurSelectFrame(QPainter& painter);
        void drawMulSelectFrame(QPainter& painter);

        void createPopupMenu();

        void showPopupMenu(QMouseEvent* event);
        void showMulSelectMenu(QMouseEvent* event);

public slots:
        void slotInsertKeyFrame();
        void slotInsertEmptyKeyFrame();
        void slotRemoveFrame();
        void slotCreateTween();
        void slotRemoveTween();
        void slotTweenToKeyFrame();
        void slotRemoveMulSelect();
        void slotCopy();
        void slotPaste();
private:
        QPoint m_lastpos;
        int m_move;
        int m_ruler_unit;
        int m_ruler_height;
        int m_frame_height;

        /* mul select */
        bool m_mulSelect;
        int m_from;
        int m_to;


        /* menu */
        QMenu* m_menu;
        QAction* ma_insertKeyFrame;
        QAction* ma_insertEmptyKeyFrame;
        QAction* ma_removeFrame;
        QAction* ma_copy;
        QAction* ma_paste;
        QAction* ma_createTween;
        QAction* ma_removeTween;
        QAction* ma_tweenToKeyFrame;

        /* mul select menu */
        QMenu* m_menuMulSelect;
        QAction* ma_mulSelectRemoveAll;
};
#endif /*_DS_ANIMATION_H_*/

