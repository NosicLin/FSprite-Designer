#ifndef _DS_SPRITE_DISPLAY_H_
#define _DS_SPRITE_DISPLAY_H_

#include <QWidget>
#include <QTreeWidget>
#include <QDockWidget>
#include <QPushButton>
#include <QMenu>
class DsSpriteTreeWidget;
class DsFrameTreeWidget;


class DsSpriteDisplay:public QWidget
{
    Q_OBJECT
    public:
        DsSpriteDisplay(QWidget* p);

    private:
        void showProject();

    private:
        QDockWidget* m_Dock;
        QTabWidget*  m_tabWidget;
        DsSpriteTreeWidget* m_spriteTreeWidget;
        DsFrameTreeWidget* m_frameTreeWidget;

        QPushButton* m_spriteButton;
        QPushButton* m_frameButton;
        QWidget*     m_widget;


};


class DsSpriteTreeWidget:public QTreeWidget
{
    Q_OBJECT
    public:
        DsSpriteTreeWidget(QWidget* parent);


    public slots:
        void slotProjectInited();
        void slotCurProjectChange();
        void slotCurAnimationChange();
        void slotCurrentItemChanged ( QTreeWidgetItem * current, QTreeWidgetItem * previous);

    protected:
        void initView();
        void createView();
        void updateView();

        //setCurProject
        void setCurProject(std::string projectName);
        //setCurAnimation
        void setCurAnimation(std::string animtionName);

    private:
        bool m_changedCausedByDsData;
        bool m_changedCausedByView;
        bool m_markCurProjectChange;


    /*  for MultMenus   */
    protected:
        void  contextMenuEvent(QContextMenuEvent *event);
    protected slots:
        /* respond m_blankMenus request */
        void slotAddSprite();
        void slotOpenSprite();

        /* respond m_spriteMenus request */
        void slotAddAnimation();
        void slotCloseSprite();
        void slotRenameSprite();

        /* respond m_animationMenus request*/
        void slotDeleteAnimation();
        void slotRenameAnimation();


    private:
        void createMultMenus();

        void createBlankMenus();
        void createSpriteMenus();
        void createAnimationMenus();
    private:
        QPoint m_cursorPos;

        //QMenu* m_multSelectMenu;

        QMenu* m_blankMenus;
        QAction* m_addSprite;
        QAction* m_openSprite;

        QMenu* m_spriteMenus;
        QAction* m_addAnimation;
        QAction* m_closeSprite;
        QAction* m_renameSprite;

        QMenu* m_animationMenus;
        QMenu* m_animationMenus1;
        QAction* m_deleteAnimation;
        QAction* m_renameAnimation;

};

class DsFrameTreeWidget:public QTreeWidget
{
    Q_OBJECT
    public:
    DsFrameTreeWidget(QWidget* parent);

public slots:
    void slotProjectRefresh();
    void slotItemClicked(QTreeWidgetItem* item,int column);
    /*
    void slotCurProjectChange();
    void slotCurAnimationChange();
    void slotCurrentItemChanged ( QTreeWidgetItem * current, QTreeWidgetItem * previous);
    */
protected:
    void initView();
    void createView();
    //setCurProject
    //void setCurProject(std::string projectName);
    //setCurAnimation
    //void setCurAnimation(std::string animtionName);
};

#endif /*_DS_SPRITE_DISPLAY_H_*/
