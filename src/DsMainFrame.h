#ifndef _DS_MAIN_FRAME_H_
#define _DS_MAIN_FRAME_H_
#include <QMainWindow>
#include <QTextStream>
#include <QStatusBar>
#include <QToolBar>
class DsMainFrame:public QMainWindow
{
    Q_OBJECT

	public:
        DsMainFrame(QWidget* parenet=0);

    private:
        void createMenuBar();
        void createStatusBar();
        void createToolBar();
	public slots:
		/* file */
        void onNew(){}
        void onOpen(){}
        void onSave(){}
        void onSaveAs(){}
        void onClose(){}
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

        /* animation */
        void onPlay(){}
        void onStop(){}
        void onAddAnimation(){}
        void onSetFrame(){}

		/* view */
        void onStatusAxis();
        void onStatusGrid();

		/* about */
        void onAbout(){}
        void onHelp(){}
        void onToggleStatusBar(){}

        /* change size */
        void onZoomIn(){}
        void onZoomOut(){}
        void onResize(){}

     public:

        /* set */
        void setGrid(bool show){}
        void setAxis(bool show){}




	private:
		/* status bar */
        QAction* m_gridStatus;
        QAction* m_axisStatus;
        QToolBar* m_toolBar;
};


#endif /*_DS_MAIN_FRAME_H_*/

