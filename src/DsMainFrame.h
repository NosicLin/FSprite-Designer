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
    QMenuBar* m_menuBar;
    QStatusBar* m_statusBar;

    DsResourceDisplay* m_resDisplay;
    DsSpriteDisplay* m_spriteDisplay;
    DsEditSpace* m_editSpace;
	DsPropertyDisplay* m_propertyDisplay;

    QWidget* m_clientArea;
};


#endif /*_DS_MAIN_FRAME_H_*/

