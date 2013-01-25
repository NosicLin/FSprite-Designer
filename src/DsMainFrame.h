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
        void onSave(){}
        void onSaveAs(){}
        void onClose(){}
        void onQuit(){}

		/* edit */
        void onPaste(){}
        void onCopy(){}

		/* view */
        void onShowGrid(bool show){}
        void onShowAxis(bool show){}

		/* about */
        void onAbout(){}
        void onHelp(){}
		void onToggleStatusBar();

	private:
		/* status bar */
        QAction* m_viewStatus;
        QToolBar* m_toolBar;
};


#endif /*_DS_MAIN_FRAME_H_*/

