#ifndef _DS_EDIT_SPACE_H_
#define _DS_EDIT_SPACE_H_
#include <QWidget.h>
#include <QTabBar.H>

#include "DsEditView.h"

#include "DsAnimationEdit.h"

class DsEditSpace:public QWidget
{
    Q_OBJECT
public:
    DsEditSpace(QWidget* parent);


public:
    void showAxis(bool enable);
    void showGrid(bool enable);
    void zoomIn();
    void zoomOut();
    void resetZoomTranslate();


protected:
    void clearTab();
    void reTabAnimation();
    int getCurAnimationIndex();

public slots:
    void slotTabbarCurrentChange(int index);

    void slotResetSprite();

    void slotCurAnimationChange();

    void slotCurFrameChange();
    void slotAnimationPropertyChange();


    void slotResFileSelect(const std::string& path,const std::string& name);

private:
    QTabBar* m_tabbar;
    bool m_markTabNotify;
    DsEditView* m_editView;
    DsAnimationEdit* m_animationEdit;
};


#endif /*_DS_EDIT_SPACE_H_*/


