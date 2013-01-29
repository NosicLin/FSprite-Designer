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
public slots:
    void slotCurProjectChange(){}
    void slotCurAnimationChange(){}
    void slotCurFrameChange();
    void slotAnimationPropertyChange();


private:
    QTabBar* m_tabbar;
    DsEditView* m_editView;
    DsAnimationEdit* m_animationEdit;
};


#endif /*_DS_EDIT_SPACE_H_*/


