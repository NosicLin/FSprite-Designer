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

    connectDataSignal();

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

    QSplitter* hsplitter=new QSplitter(Qt::Horizontal,m_clientArea);
    setCentralWidget(hsplitter);

    //QHBoxLayout* hlayout= new QHBoxLayout(m_clientArea);


    QTabWidget* left=new QTabWidget();
    left->setElideMode(Qt::ElideRight);
    left->setMovable(1);
    left->setDocumentMode(1);
    left->addTab(m_resDisplay,QString("Resource"));
    left->addTab(m_propertyDisplay,QString("Property"));



    /*
    hlayout->addWidget(left);
    hlayout->addWidget(m_editSpace,1);
    hlayout->addWidget(m_spriteDisplay);
    */
    hsplitter->addWidget(left);
    hsplitter->addWidget(m_editSpace);
    hsplitter->addWidget(m_spriteDisplay);

    hsplitter->setStretchFactor(1,1);

    //hlayout->setStretchFactor(1,1);

    //hsplitter->addWidget(m_spriteDisplay);

    QHBoxLayout* hbox=new QHBoxLayout(this);
    hbox->addWidget(m_clientArea);
    setLayout(hbox);

    //m_clientArea->setLayout(hlayout);



}

void DsMainFrame::createDialog()
{
    /* about dialog */
    m_aboutDialog=new QDialog;
    Ui_AboutDialog ui_about;
    ui_about.setupUi(m_aboutDialog);

    /* scale dialog */
}

void DsMainFrame::connectDataSignal()
{
    DsData* data=DsData::shareData();
    connect(data,SIGNAL(signalCurProjectChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalCurSpriteChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalCurAnimationChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalCurFrameChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalCurFrameImageChange()),this,SLOT(slotDataChange()));

    connect(data,SIGNAL(signalProjectPropertyChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalAnimationPropertyChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalFramePropertyChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalFrameImagePropertyChange()),this,SLOT(slotDataChange()));
    connect(data,SIGNAL(signalAnimationPlayStateChange()),this,SLOT(slotDataChange()));

}
void DsMainFrame::slotDataChange()
{
    configToolBar();
    configMenuBar();
}

void DsMainFrame::configToolBar()
{
    DsData* data=DsData::shareData();
    bool anim_play=DsOperator::animation()->isAnimationPlay();
	DsProject* project=data->getProject();
	tl_new->setEnabled(true);
	tl_undo->setEnabled(true);
	tl_redo->setEnabled(true);
	tl_moveUp->setEnabled(true);
	tl_moveDown->setEnabled(true);
	tl_moveFront->setEnabled(true);
	tl_moveEnd->setEnabled(true);
	tl_play->setEnabled(true);
	tl_stop->setEnabled(false);
	if(project==NULL)
	{
		tl_new->setEnabled(false);
		tl_undo->setEnabled(false);
		tl_redo->setEnabled(false);
		tl_moveUp->setEnabled(false);
		tl_moveDown->setEnabled(false);
		tl_moveFront->setEnabled(false);
		tl_moveEnd->setEnabled(false);
		tl_play->setEnabled(false);
		tl_stop->setEnabled(false);
		return ;
	}
	if(anim_play)
	{
		tl_new->setEnabled(false);
		tl_undo->setEnabled(false);
		tl_redo->setEnabled(false);
		tl_moveUp->setEnabled(false);
		tl_moveDown->setEnabled(false);
		tl_moveFront->setEnabled(false);
		tl_moveEnd->setEnabled(false);
		tl_play->setEnabled(false);
		tl_stop->setEnabled(true);
		return;
	}

    DsFrameImage* cur_frame_image=data->getCurFrameImage();
	if(cur_frame_image==NULL)
	{
		tl_moveUp->setEnabled(false);
		tl_moveDown->setEnabled(false);
		tl_moveFront->setEnabled(false);
		tl_moveEnd->setEnabled(false);
	}
	bool can_undo=DsOperator::aux()->canUndo();
	bool can_redo=DsOperator::aux()->canRedo();
	tl_undo->setEnabled(can_undo);
	tl_redo->setEnabled(can_redo);
}
void DsMainFrame::configMenuFile()
{
    DsData* data=DsData::shareData();
    DsProject* proj=data->getProject();
    DsSprite* sprite=data->getCurSprite();
    ms_newSprite->setEnabled(proj!=NULL);
    ms_close->setEnabled(proj!=NULL);
    ms_save->setEnabled(proj!=NULL);
    ms_export->setEnabled(sprite!=NULL);
}

void DsMainFrame::configMenuView()
{

}

void DsMainFrame::configMenuAnimation()
{

    DsData* data=DsData::shareData();
    DsSprite* sprite=data->getCurSprite();
    bool anim_play=DsOperator::animation()->isAnimationPlay();
    if(!sprite)
    {
        ms_play->setEnabled(false);
        ms_stop->setEnabled(false);
        ms_add_animation->setEnabled(false);
        ms_set_frame->setEnabled(false);
        return;
    }
    if(anim_play)
    {
        ms_play->setEnabled(false);
        ms_stop->setEnabled(true);
        ms_add_animation->setEnabled(false);
        ms_set_frame->setEnabled(false);
        return;
    }

    ms_add_animation->setEnabled(true);

    DsAnimation* anim=data->getCurAnimation();
    ms_set_frame->setEnabled(anim!=NULL);

    ms_play->setEnabled(true);
    ms_stop->setEnabled(false);
}
void DsMainFrame::configMenuEdit()
{
    DsData* data=DsData::shareData();
    bool anim_play=DsOperator::animation()->isAnimationPlay();
    if(anim_play)
    {
        ms_undo->setEnabled(false);
        ms_redo->setEnabled(false);
        ms_moveUp->setEnabled(false);
        ms_moveDown->setEnabled(false);
        ms_moveFront->setEnabled(false);
        ms_moveEnd->setEnabled(false);
        return ;
    }
    bool can_undo=DsOperator::aux()->canUndo();
    bool can_redo=DsOperator::aux()->canRedo();
    ms_undo->setEnabled(can_undo);
    ms_redo->setEnabled(can_redo);
    DsFrameImage* cur_frame_image=data->getCurFrameImage();
    if(cur_frame_image==NULL)
    {
        ms_moveUp->setEnabled(false);
        ms_moveDown->setEnabled(false);
        ms_moveFront->setEnabled(false);
        ms_moveEnd->setEnabled(false);
    }
    else
    {
        ms_moveUp->setEnabled(true);
        ms_moveDown->setEnabled(true);
        ms_moveFront->setEnabled(true);
        ms_moveEnd->setEnabled(true);
    }
}
void DsMainFrame::configMenuBar()
{
    configMenuFile();
    configMenuEdit();
    configMenuView();
    configMenuAnimation();
}
void DsMainFrame::onAbout()
{

    m_aboutDialog->show();
}


void DsMainFrame::onStatusAxis()
{
    if(ms_viewAxis->isChecked())
    {
        m_editSpace->showAxis(true); }
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
    DsOperator::data()->newSprite();
}

void DsMainFrame::onSave()
{
    DsOperator::io()->saveProject();
}
void DsMainFrame::onClose()
{
    DsOperator::io()->closeProject();
}

void DsMainFrame::onNewProject()
{
    DsOperator::io()->newProject();
}

void DsMainFrame::onExport()
{
    DsDebug<<"Export"<<endl;

    DsSprite* sprite=DsData::shareData()->getCurSprite();
    if(sprite)
    {
        DsOperator::io()->exportFSprite(sprite->getID());
    }
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


void DsMainFrame::onUndo()
{
    DsOperator::aux()->undo();
}

void DsMainFrame::onRedo()
{
    DsOperator::aux()->redo();
}










