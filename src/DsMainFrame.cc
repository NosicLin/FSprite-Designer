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
        QAction* ms_new=new QAction(QPixmap(DS_MS_NEW),"&New...",this);
		mn_file->addAction(ms_new);
		connect(ms_new,SIGNAL(triggered()),this,SLOT(onNew()));


		/* open */
        QAction* ms_open=new QAction(QPixmap(DS_MS_OPEN),"&Open...",this);
		mn_file->addAction(ms_open);
		connect(ms_open,SIGNAL(triggered()),this,SLOT(onOpen()));

        /* save */
        QAction* ms_save=new QAction(QPixmap(DS_MS_OPEN),"&Save",this);
        mn_file->addAction(ms_save);
        connect(ms_save,SIGNAL(triggered()),this,SLOT(onSave()));

        /* save as */
        QAction* ms_save_as=new QAction(QPixmap(DS_MS_OPEN),"&Save As...",this);
        mn_file->addAction(ms_save_as);
        connect(ms_save_as,SIGNAL(triggered()),this,SLOT(onSaveAs()));

        /* close */
        QAction* ms_close=new QAction(QPixmap(DS_MS_OPEN),"&Close",this);
        mn_file->addAction(ms_close);
        connect(ms_close,SIGNAL(triggered()),this,SLOT(onClose()));

        /* export  */
        QAction* ms_export=new QAction(QPixmap(DS_MS_OPEN),"&Export...",this);
        mn_file->addAction(ms_export);
        connect(ms_export,SIGNAL(triggered()),this,SLOT(onExport()));

        /* quit */
        QAction* ms_quit=new QAction(QPixmap(DS_MS_OPEN),"&Quit",this);
        mn_file->addAction(ms_quit);
        connect(ms_quit,SIGNAL(triggered()),this,SLOT(onQuit()));


	}


	/* Edit */
	QMenu* mn_edit=menuBar()->addMenu("&Edit");
	{

        /* undo */
        QAction* ms_undo=new QAction(QPixmap(DS_MS_UNDO),"&Undo",this);
        mn_edit->addAction(ms_undo);
        connect(ms_undo,SIGNAL(triggered()),this,SLOT(onUndo()));

         /* redo */
        QAction* ms_redo=new QAction(QPixmap(DS_MS_REDO),"&Redo",this);
        mn_edit->addAction(ms_redo);
        connect(ms_redo,SIGNAL(triggered()),this,SLOT(onRedo()));

        /* Paste */
        QAction* ms_paste=new QAction(QPixmap(DS_MS_PASTE),"&Paste",this);
		mn_edit->addAction(ms_paste);
		connect(ms_paste,SIGNAL(triggered()),this,SLOT(onPaste()));

        /* Copy */
       QAction* ms_copy=new QAction(QPixmap(DS_MS_COPY),"&Copy",this);
       mn_edit->addAction(ms_copy);
       connect(ms_copy,SIGNAL(triggered()),this,SLOT(onCopy()));

        /* rotate */
       QAction* ms_rotate=new QAction(QPixmap(DS_MS_ROTATE),"&Rotate",this);
       mn_edit->addAction(ms_rotate);
       connect(ms_rotate,SIGNAL(triggered()),this,SLOT(onRotate()));

        /* scale */
       QAction* ms_scale=new QAction(QPixmap(DS_MS_SCALE),"&Scale",this);
       mn_edit->addAction(ms_scale);
       connect(ms_scale,SIGNAL(triggered()),this,SLOT(onScale()));

       /* position */
       QAction* ms_position=new QAction(QPixmap(DS_MS_POSITION),"&Redo",this);
       mn_edit->addAction(ms_position);
       connect(ms_position,SIGNAL(triggered()),this,SLOT(onPosition()));


	}


	/* view */
	QMenu* mn_view=menuBar()->addMenu("&View");
	{

        /*show Axis*/
        QAction* ms_view_axis=new QAction("&Show Axis",this);
        ms_view_axis->setCheckable(true);
        ms_view_axis->setChecked(true);
        mn_view->addAction(ms_view_axis);
        connect(ms_view_axis,SIGNAL(triggered()),this,SLOT(onStatusAxis()));
        m_axisStatus=ms_view_axis;

        /* show grid */
        QAction* ms_view_grid=new QAction("&View Status",this);
        ms_view_grid->setCheckable(true);
        ms_view_grid->setChecked(true);
        mn_view->addAction(ms_view_grid);
        connect(ms_view_grid,SIGNAL(triggered()),this,SLOT(onStatusGrid()));
        m_gridStatus=ms_view_grid;

    }
    /* animation */
    QMenu* mn_animation=menuBar()->addMenu("Animation");
    {
        /* play */
        QAction* ms_play=new QAction(QPixmap(DS_MS_PLAY),"&Play",this);
        mn_animation->addAction(ms_play);
        connect(ms_play,SIGNAL(triggered()),this,SLOT(onPlay()));

        /* stop */
        QAction* ms_stop=new QAction(QPixmap(DS_MS_STOP),"&Stop",this);
        mn_animation->addAction(ms_stop);
        connect(ms_stop,SIGNAL(triggered()),this,SLOT(onStop()));

        /* add animation */
        QAction* ms_add_animation=new QAction(QPixmap(DS_MS_ADD_ANIMATION),"&Add Animation",this);
        mn_animation->addAction(ms_add_animation);
        connect(ms_add_animation,SIGNAL(triggered()),this,SLOT(onAddAnimation()));

        /* set frame */
        QAction* ms_set_frame=new QAction(QPixmap(DS_MS_SET_FRAME),"&Frame",this);
        mn_animation->addAction(ms_set_frame);
        connect(ms_set_frame,SIGNAL(triggered()),this,SLOT(onSetFrame()));
    }

    /* about */
    QMenu* mn_about=menuBar()->addMenu("About");
    {
        /* online toturial*/
        QAction* ms_help=new QAction(QPixmap(DS_MS_HELP),"&Online Tutorial",this);
        mn_about->addAction(ms_help);
        connect(ms_help,SIGNAL(triggered()),this,SLOT(onHelp()));

        /* about us */
        QAction* ms_about_us=new QAction(QPixmap(DS_MS_ABOUT_US),"&About Us",this);
        mn_about->addAction(ms_about_us);
        connect(ms_about_us,SIGNAL(triggered()),this,SLOT(onAbout()));
    }

}

void DsMainFrame::createStatusBar()
{
    statusBar();
}

void DsMainFrame::createToolBar()
{
	QToolBar* m_toolBar=addToolBar("Tool");

    /* New File */
	QAction* tl_new=m_toolBar->addAction(QIcon(DS_TL_NEW),"New File");
	connect(tl_new,SIGNAL(triggered()),this,SLOT(onNew()));

    /* Open File */
	QAction* tl_open=m_toolBar->addAction(QIcon(DS_TL_OPEN),"Qpen File");
	connect(tl_open,SIGNAL(triggered()),this,SLOT(onOpen()));

    /* Save file */
    QAction* tl_save=m_toolBar->addAction(QIcon(DS_TL_SAVE),"Save File");
    connect(tl_save,SIGNAL(triggered()),this,SLOT(onSave()));

     m_toolBar->addSeparator();

    /* Play animation*/
    QAction* tl_play=m_toolBar->addAction(QIcon(DS_TL_PLAY),"Play Animation");
    connect(tl_play,SIGNAL(triggered()),this,SLOT(onPlay()));

    /* Stop animation */
    QAction* tl_stop=m_toolBar->addAction(QIcon(DS_TL_STOP),"Stop Animation");
    connect(tl_stop,SIGNAL(triggered()),this,SLOT(onStop()));

    m_toolBar->addSeparator();

    /* Undo */
    QAction* tl_undo=m_toolBar->addAction(QIcon(DS_TL_SAVE),"Undo");
    connect(tl_undo,SIGNAL(triggered()),this,SLOT(onUndo()));
    /*Redo */
    QAction* tl_redo=m_toolBar->addAction(QIcon(DS_TL_REDO),"Redo");
    connect(tl_redo,SIGNAL(triggered()),this,SLOT(onRedo()));

    m_toolBar->addSeparator();

    /* Zoom in */
    QAction* tl_zoom_in=m_toolBar->addAction(QIcon(DS_TL_ZOOM_IN),"Zoom In");
    connect(tl_zoom_in,SIGNAL(triggered()),this,SLOT(onZoomIn()));

    /* Zoom Out */
    QAction* tl_zoom_out=m_toolBar->addAction(QIcon(DS_TL_ZOOM_OUT),"Zoom Out");
    connect(tl_zoom_out,SIGNAL(triggered()),this,SLOT(onZoomOut()));


    /* Resize */
    QAction* tl_resize=m_toolBar->addAction(QIcon(DS_TL_RESIZE),"Resize");
    connect(tl_resize,SIGNAL(triggered()),this,SLOT(onResize()));

    m_toolBar->addSeparator();

    /* Help */
    QAction* tl_help=m_toolBar->addAction(QIcon(DS_TL_HELP),"Help");
    connect(tl_help,SIGNAL(triggered()),this,SLOT(onHelp()));


}

/* slot */

void DsMainFrame::onStatusAxis()
{
    QTextStream out(stdout);
    out<<"hello statubar\n";
    setAxis(m_axisStatus->isChecked());

}
void DsMainFrame::onStatusGrid()
{
    QTextStream out(stdout);
    out<<"hello statubar\n";
    setGrid(m_gridStatus->isChecked());
}














