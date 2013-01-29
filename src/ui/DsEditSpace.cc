#include <QLabel>
#include <QTabBar>
#include "DsEditSpace.h"
#include <QVBoxLayout>


DsEditSpace::DsEditSpace(QWidget* parent)
    :QWidget(parent)
{
    QVBoxLayout* vlayout=new QVBoxLayout(this);

    m_tabbar=new QTabBar(this);
    m_tabbar->insertTab(0,"Jump");
    m_tabbar->insertTab(1,"Run");
    m_tabbar->setExpanding(false);

    m_editView=new DsEditView(this);
    m_animationEdit=new DsAnimationEdit(this);


    vlayout->addWidget(m_tabbar);
    vlayout->addWidget(m_editView,1);
    vlayout->addWidget(m_animationEdit,0,Qt::AlignBottom);

    setLayout(vlayout);
}

