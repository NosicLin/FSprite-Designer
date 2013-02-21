#ifndef _DS_SPRITE_DISPLAY_H_
#define _DS_SPRITE_DISPLAY_H_

#include <QWidget>
#include <QTreeWidget>
#include <QDockWidget>
#include <QPushButton>

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
        void initView();
        void updateView();

    public slots:
        void slotProjectInited();
        void slotCurProjectChange();
        void slotCurAnimationChange();

        void slotCurrentItemChanged ( QTreeWidgetItem * current, QTreeWidgetItem * previous);

    public:
        //setCurProject
        void DsSpriteTreeWidget::setCurProject(std::string projectName);

        //setCurAnimation
        void DsSpriteTreeWidget::setCurAnimation(std::string animtionName);

    private:
        bool m_changedCausedByDsData;
        bool m_changedCausedByView;
        bool m_markCurProjectChange;


};
class DsFrameTreeWidget:public QTreeWidget
{
    Q_OBJECT
    public:
    DsFrameTreeWidget(QWidget* parent);

};

#endif /*_DS_SPRITE_DISPLAY_H_*/
