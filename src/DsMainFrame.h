#ifndef _DS_MAIN_FRAME_H_
#define _DS_MAIN_FRAME_H_
#include <QMainWindow>
#include <QTextStream>
class DsMainFrame:public QMainWindow
{
    Q_OBJECT

	public:
        DsMainFrame(QWidget* parenet=0);
    private:
        void createMenuBar();
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
};


#endif /*_DS_MAIN_FRAME_H_*/

