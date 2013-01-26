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
    /* status bar */
    QAction* m_viewStatus;
};


#endif /*_DS_MAIN_FRAME_H_*/

