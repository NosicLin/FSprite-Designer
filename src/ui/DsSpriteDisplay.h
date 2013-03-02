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
        void slotCurSpriteChange();
        void slotCurAnimationChange();
        void slotCurrentItemChanged ( QTreeWidgetItem * current, QTreeWidgetItem * previous);

    protected:
        void initView();
        void createView();
        void updateView();

        void setActionTypeToNone(){ m_actionType = MENUS_ACT_NONE;}

    private:
        bool m_changedCausedByDsData;
        bool m_changedCausedByView;
        bool m_markCurProjectChange;

    protected:
        /*  for MultMenus   */
        void  contextMenuEvent(QContextMenuEvent *event);
    protected slots:
        /* respond m_blankMenus request */
        void slotNewProject();
        void slotOpenProject();


        /* respond m_projectMenus request */
        void slotAddSprite();
        void slotSaveProject();
        void slotCloseProject();

        /* respond m_spriteMenus request */
        void slotAddAnimation();
        void slotRemoveSprite();
        void slotRenameSprite();
        void slotExportSprite();

        /* respond m_animationMenus request */
        void slotRemoveAnimation();
        void slotRenameAnimation();

        /* deal with item changed signal */
        void slotItemChanged(QTreeWidgetItem * item, int column);
        void slotItemDoubleClicked(QTreeWidgetItem * item, int column);

    private:
        void createMultMenus();

        void createBlankMenus();
        void createProjectMenus();
        void createSpriteMenus();
        void createAnimationMenus();
    private:
        QPoint m_cursorPos;

        //QMenu* m_multSelectMenu;
        QMenu* m_blankMenus;
        QAction* m_newProject;
        QAction* m_openProject;

        QMenu* m_projectMenus;
        QAction* m_addSprite;
        QAction* m_save;
        QAction* m_close;

        QMenu* m_spriteMenus;
        QAction* m_addAnimation;
        QAction* m_removeSprite;
        QAction* m_renameSprite;
        QAction* m_exportSprite;

        QMenu* m_animationMenus;
        QAction* m_removeAnimation;
        QAction* m_renameAnimation;

        QString originalName;
        int m_actionType;

        enum
        {
            MENUS_ACT_RENAME_SPRITE = 0,
            MENUS_ACT_RENAME_ANIMATION,
            MENUS_ACT_REMOVE_ANIMATION,
            MENUS_ACT_REMOVE_SPRITE,
            MENUS_ACT_SAVE_SPRITE,
            MENUS_ACT_SAVE_PROJECT,
            MENUS_ACT_NONE
        };
};

class DsFrameTreeWidget:public QTreeWidget
{
    Q_OBJECT
    public:
    DsFrameTreeWidget(QWidget* parent);

public slots:
    void slotProjectRefresh();
    void slotItemClicked(QTreeWidgetItem* item,int column);

protected:
    void initView();
    void createView();

};

#endif /*_DS_SPRITE_DISPLAY_H_*/
