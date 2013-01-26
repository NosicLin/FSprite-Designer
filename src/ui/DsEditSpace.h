#ifndef _DS_EDIT_SPACE_H_
#define _DS_EDIT_SPACE_H_
#include <QWidget.h>
#include <QTabBar.H>

#include "DsEditView.h"

class DsEditSpace:public QWidget
{
    Q_OBJECT
public:
    DsEditSpace(QWidget* parent);
private:
    QTabBar* m_tabbar;
    DsEditView* m_editView;



};


#endif /*_DS_EDIT_SPACE_H_*/


