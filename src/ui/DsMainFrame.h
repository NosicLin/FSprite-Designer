#ifndef _DS_MAIN_FRAME_H_
#define _DS_MAIN_FRAME_H_
#include <QMainWindow>
#include <QTextStream>
#include <QStatusBar>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>


#include "DsResourceDisplay.h"
#include "DsEditSpace.h"
#include "DsSpriteDisplay.h"
#include "DsPropertyDisplay.h"

class DsMainFrame:public QMainWindow
{
	Q_OBJECT

	public:
		DsMainFrame(QWidget* parenet=0);

	private:

		void createMenuBar();
		void createStatusBar();
		void createToolBar();
		void createResourceDisplay();
		void createEditSpace();
		void createSpriteDisplay();
		void createPropertyDisplay();
		void createDialog();
		void initLayout();



	private:

		QToolBar* m_toolBar;
		QMenuBar* m_menuBar;
		QStatusBar* m_statusBar;

		DsResourceDisplay* m_resDisplay;
        DsSpriteDisplay* m_spriteDisplay;
        DsEditSpace* m_editSpace;
        DsPropertyDisplay* m_propertyDisplay;

		QWidget* m_clientArea;

        public slots:
            /* file */
        void onNewProject();
        void onOpenProject();
        void onSave();
        void onClose(){}
        void onNewSprite();

		void onExport(){}
		void onQuit(){}

		/* edit */
		void onPaste(){}
		void onCopy(){}
		void onUndo(){}
		void onRedo(){}
		void onRotate(){}
		void onScale(){}
        void onPosition(){}

        void onMoveUp();
        void onMoveDown();
        void onMoveFront();
        void onMoveEnd();

		/* animation */
        void onPlay();
        void onStop();
        void onAddAnimation();
		void onSetFrame(){}

		/* view */
		void onStatusAxis();
		void onStatusGrid();
		void onAddBackground(){}

		/* about */
		void onAbout();
		void onHelp(){}
		void onToggleStatusBar(){}

		/* change size */
        void onZoomIn();
        void onZoomOut();
        void onResetZoomTranslate();

	private:
		QDialog* m_aboutDialog;

	private:
		/* file */
        QAction* ms_newProject;
        QAction* ms_openProject;
        QAction* ms_newSprite;

        QAction* ms_save;

		QAction* ms_close;
		QAction* ms_export;
		QAction* ms_quit;

		/* edit */
		QAction* ms_undo;
		QAction* ms_redo;
		QAction* ms_paste;
		QAction* ms_copy;
		QAction* ms_rotate;
		QAction* ms_scale;
		QAction* ms_position;
        QAction* ms_moveUp;
        QAction* ms_moveDown;
        QAction* ms_moveFront;
        QAction* ms_moveEnd;

		/* view */
        QAction* ms_viewAxis;
        QAction* ms_viewGrid;
        QAction* ms_zoomOut;
        QAction* ms_zoomIn;
        QAction* ms_resetZoomTranslate;
        QAction* ms_addBackgroud;

		/* animation */
		QAction* ms_play;
		QAction* ms_stop;
		QAction* ms_add_animation;
		QAction* ms_set_frame;

		/* about */
		QAction* ms_help;
		QAction* ms_about_us;


		/* tool bar */
		QAction* tl_new;
		QAction* tl_open;
		QAction* tl_save;
		QAction* tl_undo;
		QAction* tl_redo;
		QAction* tl_moveUp;
		QAction* tl_moveDown;
		QAction* tl_moveFront;
		QAction* tl_moveEnd;
		QAction* tl_play;
		QAction* tl_stop;
		QAction* tl_zoom_in;
		QAction* tl_zoom_out;
		QAction* tl_resize;
		QAction* tl_background;
		QAction* tl_help;


};


#endif /*_DS_MAIN_FRAME_H_*/

































