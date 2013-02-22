#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextStream>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>

#include "DsMainFrame.h"
#include "DsQrcMacros.h"
#include "operator/DsOperator.h"
#include "util/DsDebug.h"

/* auto gernert files */
#include "ui_about.h"


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
	createDialog();
	initLayout();
	connect(m_resDisplay,SIGNAL(resFileSelect(const std::string& ,const std::string& )),
			m_editSpace,SLOT(slotResFileSelect(const std::string&,const std::string& )));
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
  //  m_spriteDisplay=new DsSpriteDisplay(m_clientArea);
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
        ms_newProject=new QAction(QPixmap(DS_MS_NEW),"&New Project",this);
        mn_file->addAction(ms_newProject);
        connect(ms_newProject,SIGNAL(triggered()),this,SLOT(onNewProject()));


		/* open */
        ms_openProject=new QAction(QPixmap(DS_MS_OPEN),"&Open Project",this);
        mn_file->addAction(ms_openProject);
        connect(ms_openProject,SIGNAL(triggered()),this,SLOT(onOpenProject()));


        ms_newSprite=new QAction(QPixmap(DS_MS_NEW),"&New Sprite",this);
        mn_file->addAction(ms_newSprite);
        connect(ms_newSprite,SIGNAL(triggered()),this,SLOT(onNewSprite()));

		/* save */
		ms_save=new QAction(QPixmap(DS_MS_SAVE),"&Save",this);
		mn_file->addAction(ms_save);
		connect(ms_save,SIGNAL(triggered()),this,SLOT(onSave()));


		/* close */
		ms_close=new QAction(QPixmap(DS_MS_CLOSE),"&Close",this);
		mn_file->addAction(ms_close);
		connect(ms_close,SIGNAL(triggered()),this,SLOT(onClose()));

		/* export  */
		ms_export=new QAction(QPixmap(DS_MS_EXPORT),"&Export...",this);
		mn_file->addAction(ms_export);
		connect(ms_export,SIGNAL(triggered()),this,SLOT(onExport()));

		/* quit */
		ms_quit=new QAction(QPixmap(DS_MS_QUIT),"&Quit",this);
		mn_file->addAction(ms_quit);
		connect(ms_quit,SIGNAL(triggered()),this,SLOT(onQuit()));


	}


	/* Edit */
	QMenu* mn_edit=menuBar()->addMenu("&Edit");
	{

		/* undo */
		ms_undo=new QAction(QPixmap(DS_MS_UNDO),"&Undo",this);
		mn_edit->addAction(ms_undo);
		connect(ms_undo,SIGNAL(triggered()),this,SLOT(onUndo()));

		/* redo */
		ms_redo=new QAction(QPixmap(DS_MS_REDO),"&Redo",this);
		mn_edit->addAction(ms_redo);
		connect(ms_redo,SIGNAL(triggered()),this,SLOT(onRedo()));

		/* moveUp */
		ms_moveUp=new QAction(QPixmap(DS_MS_MOVE_UP),"&MoveUp",this);
		mn_edit->addAction(ms_moveUp);
		connect(ms_moveUp,SIGNAL(triggered()),this,SLOT(onMoveUp()));

		/* down */
		ms_moveDown=new QAction(QPixmap(DS_MS_MOVE_DOWN),"&MoveDown",this);
		mn_edit->addAction(ms_moveDown);
		connect(ms_moveDown,SIGNAL(triggered()),this,SLOT(onMoveDown()));

		/* tofront */
		ms_moveFront=new QAction(QPixmap(DS_MS_MOVE_FRONT),"&MoveFront",this);
		mn_edit->addAction(ms_moveFront);
		connect(ms_moveFront,SIGNAL(triggered()),this,SLOT(onMoveFront()));

		/* toend */
		ms_moveEnd=new QAction(QPixmap(DS_MS_MOVE_END),"&MoveEnd",this);
		mn_edit->addAction(ms_moveEnd);
		connect(ms_moveEnd,SIGNAL(triggered()),this,SLOT(onMoveEnd()));



		/* Paste */
		ms_paste=new QAction(QPixmap(DS_MS_PASTE),"&Paste",this);
		mn_edit->addAction(ms_paste);
		connect(ms_paste,SIGNAL(triggered()),this,SLOT(onPaste()));

		/* Copy */
		ms_copy=new QAction(QPixmap(DS_MS_COPY),"&Copy",this);
		mn_edit->addAction(ms_copy);
		connect(ms_copy,SIGNAL(triggered()),this,SLOT(onCopy()));

		/* rotate */
		ms_rotate=new QAction(QPixmap(DS_MS_ROTATE),"&Rotate",this);
		mn_edit->addAction(ms_rotate);
		connect(ms_rotate,SIGNAL(triggered()),this,SLOT(onRotate()));

		/* scale */
		ms_scale=new QAction(QPixmap(DS_MS_SCALE),"&Scale",this);
		mn_edit->addAction(ms_scale);
		connect(ms_scale,SIGNAL(triggered()),this,SLOT(onScale()));

		/* position */
		ms_position=new QAction(QPixmap(DS_MS_POSITION),"&Position",this);
		mn_edit->addAction(ms_position);
		connect(ms_position,SIGNAL(triggered()),this,SLOT(onPosition()));


	}


	/* view */
	QMenu* mn_view=menuBar()->addMenu("&View");
	{

		/*show Axis*/
        ms_viewAxis=new QAction("&Show Axis",this);
        ms_viewAxis->setCheckable(true);
        ms_viewAxis->setChecked(true);
        mn_view->addAction(ms_viewAxis);
        connect(ms_viewAxis,SIGNAL(triggered()),this,SLOT(onStatusAxis()));

		/* show grid */
        ms_viewGrid=new QAction("&View Grid",this);
        ms_viewGrid->setCheckable(true);
        ms_viewGrid->setChecked(false);
        mn_view->addAction(ms_viewGrid);
        connect(ms_viewGrid,SIGNAL(triggered()),this,SLOT(onStatusGrid()));


        ms_addBackgroud=new QAction(QPixmap(DS_MS_BACKGROUND),"&Add Background Image",this);
        mn_view->addAction(ms_addBackgroud);
        connect(ms_addBackgroud,SIGNAL(triggered()),this,SLOT(onAddBackground()));
    }

	/* animation */
	QMenu* mn_animation=menuBar()->addMenu("Animation");
	{
		/* play */
		ms_play=new QAction(QPixmap(DS_MS_PLAY),"&Play",this);
		mn_animation->addAction(ms_play);
		connect(ms_play,SIGNAL(triggered()),this,SLOT(onPlay()));

		/* stop */
		ms_stop=new QAction(QPixmap(DS_MS_STOP),"&Stop",this);
		mn_animation->addAction(ms_stop);
		connect(ms_stop,SIGNAL(triggered()),this,SLOT(onStop()));

		/* add animation */
		ms_add_animation=new QAction(QPixmap(DS_MS_ADD_ANIMATION),"&Add Animation",this);
		mn_animation->addAction(ms_add_animation);
		connect(ms_add_animation,SIGNAL(triggered()),this,SLOT(onAddAnimation()));

		/* set frame */
		ms_set_frame=new QAction(QPixmap(DS_MS_SET_FRAME),"&Frame",this);
		mn_animation->addAction(ms_set_frame);
		connect(ms_set_frame,SIGNAL(triggered()),this,SLOT(onSetFrame()));
	}

	/* about */
	QMenu* mn_about=menuBar()->addMenu("About");
	{
		/* online toturial*/
		ms_help=new QAction(QPixmap(DS_MS_HELP),"&Online Tutorial",this);
		mn_about->addAction(ms_help);
		connect(ms_help,SIGNAL(triggered()),this,SLOT(onHelp()));

		/* about us */
		ms_about_us=new QAction(QPixmap(DS_MS_ABOUT_US),"&About Us",this);
		mn_about->addAction(ms_about_us);
		connect(ms_about_us,SIGNAL(triggered()),this,SLOT(onAbout()));
	}

}

void DsMainFrame::createStatusBar()
{
	m_statusBar=statusBar();
}

void DsMainFrame::createToolBar()
{
	QToolBar* m_toolBar=new QToolBar;
	addToolBar(Qt::RightToolBarArea,m_toolBar);

	/* New File */
    tl_new=m_toolBar->addAction(QIcon(DS_TL_NEW),"New Sprite");
    connect(tl_new,SIGNAL(triggered()),this,SLOT(onNewSprite()));

	m_toolBar->addSeparator();

	/* Undo */
	tl_undo=m_toolBar->addAction(QIcon(DS_TL_UNDO),"Undo");
	connect(tl_undo,SIGNAL(triggered()),this,SLOT(onUndo()));
	/*Redo */
	tl_redo=m_toolBar->addAction(QIcon(DS_TL_REDO),"Redo");
	connect(tl_redo,SIGNAL(triggered()),this,SLOT(onRedo()));

	m_toolBar->addSeparator();

	/* Up */
	tl_moveUp=m_toolBar->addAction(QIcon(DS_TL_MOVE_UP),"MoveUp");
	connect(tl_moveUp,SIGNAL(triggered()),this,SLOT(onMoveUp()));

	/* down */
	tl_moveDown=m_toolBar->addAction(QIcon(DS_TL_MOVE_DOWN),"MoveDown");
    connect(tl_moveDown,SIGNAL(triggered()),this,SLOT(onMoveDown()));

	/* tofront */
	tl_moveFront=m_toolBar->addAction(QIcon(DS_TL_MOVE_FRONT),"MoveFront");
	connect(tl_moveFront,SIGNAL(triggered()),this,SLOT(onMoveFront()));

	/* toEnd */
	tl_moveEnd=m_toolBar->addAction(QIcon(DS_TL_MOVE_END),"MoveEnd");
	connect(tl_moveEnd,SIGNAL(triggered()),this,SLOT(onMoveEnd()));


	/* Play animation*/
	tl_play=m_toolBar->addAction(QIcon(DS_TL_PLAY),"Play Animation");
	connect(tl_play,SIGNAL(triggered()),this,SLOT(onPlay()));

	/* Stop animation */
	tl_stop=m_toolBar->addAction(QIcon(DS_TL_STOP),"Stop Animation");
	connect(tl_stop,SIGNAL(triggered()),this,SLOT(onStop()));

	m_toolBar->addSeparator();


	/* Zoom in */
	tl_zoom_in=m_toolBar->addAction(QIcon(DS_TL_ZOOM_IN),"Zoom In");
	connect(tl_zoom_in,SIGNAL(triggered()),this,SLOT(onZoomIn()));

	/* Zoom Out */
	tl_zoom_out=m_toolBar->addAction(QIcon(DS_TL_ZOOM_OUT),"Zoom Out");
	connect(tl_zoom_out,SIGNAL(triggered()),this,SLOT(onZoomOut()));


	/* Resize */
    tl_resize=m_toolBar->addAction(QIcon(DS_TL_RESIZE),"resetZoomTranslate");
    connect(tl_resize,SIGNAL(triggered()),this,SLOT(onResetZoomTranslate()));

	m_toolBar->addSeparator();

	/* Add background image */
	tl_background=m_toolBar->addAction(QIcon(DS_TL_BACKGROUND),"Add Background Image");
	connect(tl_background,SIGNAL(triggered()),this,SLOT(onAddBackground()));

	m_toolBar->addSeparator();


	/* Help */
	tl_help=m_toolBar->addAction(QIcon(DS_TL_HELP),"Help");
	connect(tl_help,SIGNAL(triggered()),this,SLOT(onHelp()));


}

void DsMainFrame::initLayout()
{

	m_clientArea->setSizePolicy(QSizePolicy::Expanding,
			QSizePolicy::Expanding);
	setCentralWidget(m_clientArea);

    QHBoxLayout* hlayout= new QHBoxLayout(m_clientArea);

    QTabWidget* left=new QTabWidget();
    left->setElideMode(Qt::ElideRight);
    left->setMovable(1);
    left->setDocumentMode(1);
    left->addTab(m_resDisplay,QString("Resource"));
    left->addTab(m_propertyDisplay,QString("Property"));



    hlayout->addWidget(left);
    hlayout->addWidget(m_editSpace,1);
    //hlayout->addWidget(m_spriteDisplay);
    //hlayout->setStretchFactor(1,1);

    //hsplitter->addWidget(m_spriteDisplay);

    //QHBoxLayout* hbox=new QHBoxLayout(m_clientArea);


    //hbox->addWidget(hlayout);
    m_clientArea->setLayout(hlayout);



}

void DsMainFrame::createDialog()
{
    /* about dialog */
    m_aboutDialog=new QDialog;
    Ui_AboutDialog ui_about;
    ui_about.setupUi(m_aboutDialog);

    /* scale dialog */
}

void DsMainFrame::onAbout()
{

	m_aboutDialog->show();
}


void DsMainFrame::onStatusAxis()
{
    if(ms_viewAxis->isChecked())
    {
        m_editSpace->showAxis(true);
    }
    else
    {
        m_editSpace->showAxis(false);
    }
}
void DsMainFrame::onStatusGrid()
{
    if(ms_viewGrid->isChecked())
    {
        m_editSpace->showGrid(true);
    }
    else
    {
        m_editSpace->showGrid(false);
    }
}

void DsMainFrame::onZoomIn()
{
    m_editSpace->zoomIn();
}
void DsMainFrame::onZoomOut()
{
    m_editSpace->zoomOut();
}
void DsMainFrame::onResetZoomTranslate()
{
    m_editSpace->resetZoomTranslate();
}
void DsMainFrame::onPlay()
{
    DsOperator::animation()->animationPlay();
}
void DsMainFrame::onStop()
{
    DsOperator::animation()->animationStop();
}

void DsMainFrame::onOpenProject()
{
    DsOperator::io()->loadProject();
}
void DsMainFrame::onNewSprite()
{
}

void DsMainFrame::onSave()
{
    DsOperator::io()->saveProject();
}

void DsMainFrame::onNewProject()
{
    DsOperator::data()->newProject();
}

void DsMainFrame::onAddAnimation()
{
    DsDebug<<"create Animation"<<endl;
    DsOperator::data()->newAnimation();
}

void DsMainFrame::onMoveUp()
{
    DsOperator::data()->frameImageMoveUp();
}

void DsMainFrame::onMoveDown()
{
    DsOperator::data()->frameImageMoveDown();
}

void DsMainFrame::onMoveFront()
{
    DsOperator::data()->frameImageMoveFront();
}

void DsMainFrame::onMoveEnd()
{
    DsOperator::data()->frameImageMoveEnd();
}











