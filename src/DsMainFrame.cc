#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextStream>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>

#include "DsMainFrame.h"
#include "DsQrcMacros.h"


DsMainFrame::DsMainFrame(QWidget* parent)
    :QMainWindow(parent)
{
    m_clientArea=new QWidget(this);
	createMenuBar();
	createStatusBar();
    createToolBar();
    createResourceDisplay();
    createEditSpace();
    createSpriteDisplay();
    createPropertyDisplay();
	initLayout();
}

void DsMainFrame::createResourceDisplay()
{
    m_resDisplay=new DsResourceDisplay(m_clientArea);
}
void DsMainFrame::createEditSpace()
{
    m_editSpace=new DsEditSpace(m_clientArea);
}

void DsMainFrame::createSpriteDisplay()
{
    m_spriteDisplay=new DsSpriteDisplay(m_clientArea);
}
void DsMainFrame::createPropertyDisplay()
{
    m_propertyDisplay=new DsPropertyDisplay(m_clientArea);
}

void DsMainFrame::createMenuBar()
{

    m_menuBar=menuBar();
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
    m_statusBar=statusBar();
}

void DsMainFrame::createToolBar()
{
    QToolBar* m_toolBar=addToolBar("MainToolBar");

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


void DsMainFrame::initLayout()
{

    m_clientArea->setSizePolicy(QSizePolicy::Expanding,
                                QSizePolicy::Expanding);
    setCentralWidget(m_clientArea);

    QSplitter* hsplitter = new QSplitter(Qt::Horizontal, m_clientArea);

 	QTabWidget* twid=new QTabWidget();
    twid->setElideMode(Qt::ElideRight);
    twid->setMovable(1);
    twid->setDocumentMode(1);
    twid->addTab(m_resDisplay,QString("Resource"));
    twid->addTab(m_propertyDisplay,QString("Property"));

    //twid->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    twid->resize(200,200);

    hsplitter->addWidget(twid);
    hsplitter->addWidget(m_editSpace);
    hsplitter->addWidget(m_spriteDisplay);

    QHBoxLayout* hbox=new QHBoxLayout(m_clientArea);



    //m_resDisplay->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    /*
    hbox->addWidget(twid,1);
    hbox->addWidget(m_editSpace,4);
    hbox->addWidget(m_spriteDisplay,1);
    */
    hbox->addWidget(hsplitter);
    m_clientArea->setLayout(hbox);



}













