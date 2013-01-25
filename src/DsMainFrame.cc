#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextStream>

#include "DsMainFrame.h"
#include "DsQrcMacros.h"


DsMainFrame::DsMainFrame(QWidget* parent)
	:QMainWindow(parent)
{
	createMenuBar();
	createStatusBar();
	createToolBar();
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


	/* view */
	QMenu* mn_view=menuBar()->addMenu("&View");
	{
        QAction* ms_view_status=new QAction("&View Status",this);
        ms_view_status->setCheckable(true);
        ms_view_status->setChecked(true);
        mn_view->addAction(ms_view_status);
		connect(ms_view_status,SIGNAL(triggered()),this,SLOT(onToggleStatusBar()));
		m_viewStatus=ms_view_status;
    }

}

void DsMainFrame::createStatusBar()
{
    statusBar();
}

void DsMainFrame::createToolBar()
{
	QToolBar* m_toolBar=addToolBar("Tool");

	QAction* tl_new=m_toolBar->addAction(QIcon(DS_TL_NEW),"New File");
	connect(tl_new,SIGNAL(triggered()),this,SLOT(onNew()));

	QAction* tl_open=m_toolBar->addAction(QIcon(DS_TL_OPEN),"Qpen File");
	connect(tl_open,SIGNAL(triggered()),this,SLOT(onOpen()));

    m_toolBar->addSeparator();

    QAction* tl_save=m_toolBar->addAction(QIcon(DS_TL_SAVE),"Save File");
    connect(tl_save,SIGNAL(triggered()),this,SLOT(onSave()));

}

/* slot */

void DsMainFrame::onToggleStatusBar()
{
    QTextStream out(stdout);
    out<<"hello statubar\n";
	if(m_viewStatus->isChecked())
    {
        out<<"Show Status\n";
		statusBar()->show();
	}
	else 
    {
        out<<"hide Status\n";
		statusBar()->hide();
	}
}















