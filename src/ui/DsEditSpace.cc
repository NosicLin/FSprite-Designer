#include <assert.h>

#include <QLabel>
#include <QTabBar>
#include "DsEditSpace.h"
#include <QVBoxLayout>
#include "model/DsData.h"
#include "util/DsDebug.h"
#include "operator/DsOperator.h"


DsEditSpace::DsEditSpace(QWidget* parent)
    :QWidget(parent)
{
    m_markTabNotify=false;
    QVBoxLayout* vlayout=new QVBoxLayout(this);

    m_tabbar=new QTabBar(this);

    m_tabbar->setExpanding(false);
    m_tabbar->setCurrentIndex(-1);
    m_tabbar->setMovable(false);
    //m_tabbar->setDrawBase(true);

    m_editView=new DsEditView(this);
    m_animationEdit=new DsAnimationEdit(this);


    vlayout->addWidget(m_tabbar);
    vlayout->addWidget(m_editView,1);
    vlayout->addWidget(m_animationEdit,0,Qt::AlignBottom);

    connect(m_tabbar,SIGNAL(currentChanged(int)),this,SLOT(slotTabbarCurrentChange(int)));


    connect(DsData::shareData(),
            SIGNAL(signalCurProjectChange()),
            this,
            SLOT(slotResetSprite()));

    connect(DsData::shareData(),
            SIGNAL(signalProjectPropertyChange()),
            this,
            SLOT(slotResetSprite()));

    connect(DsData::shareData(),
            SIGNAL(signalCurSpriteChange()),
            this,
            SLOT(slotResetSprite()));

    connect(DsData::shareData(),
            SIGNAL(signalCurAnimationChange()),
            this,
            SLOT(slotCurAnimationChange()));

    connect(DsData::shareData(),
            SIGNAL(signalCurFrameChange()),
            this,
            SLOT(slotCurFrameChange()));

    connect(DsData::shareData(),
            SIGNAL(signalCurFrameImageChange()),
            this,
            SLOT(slotCurFrameChange()));

    connect(DsData::shareData(),
            SIGNAL(signalFrameImagePropertyChange()),
            this,
            SLOT(slotFrameImagePropertyChange()));

    connect(DsData::shareData(),
            SIGNAL(signalFramePropertyChange()),
            this,
            SLOT(slotCurFrameChange()));

    connect(DsData::shareData(),
            SIGNAL(signalAnimationPropertyChange()),
            this,
            SLOT(slotAnimationPropertyChange()));

   setLayout(vlayout);
}


void DsEditSpace::showAxis(bool enable)
{
    m_editView->setShowAxis(enable);
}
void DsEditSpace::showGrid(bool enable)
{
    m_editView->setShowGrid(enable);
}
void DsEditSpace::zoomIn()
{
    m_editView->zoomIn();
}
void DsEditSpace::zoomOut()
{
    m_editView->zoomOut();
}
void DsEditSpace::resetZoomTranslate()
{
    m_editView->resetZoomTranslate();
}


void DsEditSpace::clearTab()
{
    int count=m_tabbar->count();
    while(count-->0)
    {
        m_tabbar->removeTab(0);
    }
}

void DsEditSpace::slotResetSprite()
{
    reTabAnimation();
    m_editView->slotCurFrameChange();
    m_editView->update();
    m_animationEdit->update();

}

void DsEditSpace::reTabAnimation()
{
    /* clear all tab */
    m_markTabNotify=true;
    clearTab();
    DsSprite* sprite=DsData::shareData()->getCurSprite();
    DsAnimation* cur_animation=DsData::shareData()->getCurAnimation();

    int cur_index=-1;
    if(sprite!=NULL)
    {
        int anim_nu=sprite->getAnimationNu();
        for(int i=0;i<anim_nu;i++)
        {
            DsAnimation* anim=sprite->getAnimation(i);
            if(anim==cur_animation)
            {
                cur_index=i;
            }
            m_tabbar->addTab(QString(anim->getName().c_str()));
        }
    }
    else
    {
        DsDebug<<"Sprite Not Find"<<endl;
    }

    m_tabbar->setCurrentIndex(cur_index);
    m_markTabNotify=false;

}
int DsEditSpace::getCurAnimationIndex()
{
    DsSprite* sprite=DsData::shareData()->getCurSprite();
    DsAnimation* cur_animation=DsData::shareData()->getCurAnimation();

    int cur_index=-1;
    if(sprite!=NULL)
    {
        int anim_nu=sprite->getAnimationNu();
        for(int i=0;i<anim_nu;i++)
        {
            DsAnimation* anim=sprite->getAnimation(i);
            if(anim==cur_animation)
            {
                cur_index=i;
                break;
            }
        }
    }
    return cur_index;
}

void DsEditSpace::slotTabbarCurrentChange(int index)
{
    if(m_markTabNotify)
    {
        return;
    }

    DsSprite* sprite=DsData::shareData()->getCurSprite();
    DsAnimation* anim=sprite->getAnimation(index);
    assert(sprite&&anim);
    DsOperator::data()->setCurAnimation(anim->getID());
}


void DsEditSpace::slotCurAnimationChange()
{
    int cur_index=getCurAnimationIndex();

    m_markTabNotify=true;
    m_tabbar->setCurrentIndex(cur_index);
    m_markTabNotify=false;

    m_editView->slotCurAnimationChange();
    m_editView->update();
    m_animationEdit->update();
}


void DsEditSpace::slotCurFrameChange()
{
    m_editView->slotCurFrameChange();
    m_editView->update();

    m_animationEdit->update();
}
void DsEditSpace::slotFrameImagePropertyChange()
{
    m_editView->update();
    m_animationEdit->update();
}

void DsEditSpace::slotAnimationPropertyChange()
{
    m_editView->slotCurFrameChange();
    m_editView->update();
    m_animationEdit->update();
}

void DsEditSpace::slotResFileSelect(const std::string& path,const std::string& name)
{
    DsDebug<<"File Select: "<<path.c_str()<<name.c_str()<<endl;
    m_editView->slotAddFrameImage(path,name);
    m_editView->update();
}





























