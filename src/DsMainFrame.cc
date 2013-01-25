#include <QMenu>
#include <QMenuBar>
#include "DsMainFrame.h"
#include "DsQrcMacros.h"


DsMainFrame::DsMainFrame(QWidget* parent)
	:QMainWindow(parent)
{
	createMenuBar();
}
void DsMainFrame::createMenuBar()
{

    /*File*/
    QMenu* mn_file=menuBar()->addMenu("&File");
	{	
		/* new */
        QAction* ms_new=new QAction(QPixmap(DS_MS_NEW),"&New",this);
		mn_file->addAction(ms_new);
		connect(ms_new,SIGNAL(triggered()),this,SLOT(onNew()));


		/* open */
		QAction* ms_open=new QAction(QPixmap(DS_MS_OPEN),"&Open",this);
		mn_file->addAction(ms_open);
		connect(ms_open,SIGNAL(triggered()),this,SLOT(onOpen()));
	}


	/* Edit */
	QMenu* mn_edit=menuBar()->addMenu("&Edit");
	{
        QAction* ms_paste=new QAction(QPixmap(DS_MS_PASTE),"&Paste",this);
		mn_edit->addAction(ms_paste);
		connect(ms_paste,SIGNAL(triggered()),this,SLOT(onPaste()));
	}


}
