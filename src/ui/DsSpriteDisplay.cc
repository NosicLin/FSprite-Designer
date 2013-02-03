#include <assert.h>
#include <QLabel>
#include "DsSpriteDisplay.h"
#include <string>
#include <QDebug>

#include <QMainWindow>
#include "operator\DsOperator.h"

#include "model\DsData.h"
#include "model\DsProject.h"
#include "model\DsSprite.h"
#include "model\DsAnimation.h"

#include "DsQrcMacros.h"

//Turn off debug output
//#define QT_NO_DEBUG_OUTPUT

#ifdef QT_NO_DEBUG_OUTPUT
#define qDebug while(false)qDebug
#endif

extern DsData* s_shareData;

QString s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

DsSpriteDisplay::DsSpriteDisplay(QWidget* parent)
    :QWidget(parent)
{

    m_Dock = new QDockWidget(tr("SpriteDisplay"),parent);
    m_Dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_tabWidget = new QTabWidget(m_Dock);
    m_Dock->setWidget(m_tabWidget);


    m_frameTreeWidget = new DsFrameTreeWidget(m_Dock);
    m_spriteTreeWidget = new DsSpriteTreeWidget(m_Dock);


   // m_spriteTreeWidget->addTopLevelItem(new QTreeWidgetItem(m_spriteTreeWidget,QStringList("123")));
    m_tabWidget->addTab(m_spriteTreeWidget,tr("Sprite"));
    m_tabWidget->addTab(m_frameTreeWidget,tr("Frame"));

    QMainWindow* MainWindow = (QMainWindow*)parent->parent();
    MainWindow->addDockWidget(Qt::RightDockWidgetArea, m_Dock);


}




//DsSpriteTreeWidget
DsSpriteTreeWidget::DsSpriteTreeWidget(QWidget* parent)
    :QTreeWidget(parent)
{

    m_changedCausedByDsData = true;
    m_changedCausedByView = false;
    m_markCurProjectChange = false;

    connect(DsData::shareData(),SIGNAL(signalDataPropertyChange()),
            this,SLOT(slotProjectInited()));

    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotCurProjectChange()));

    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotCurAnimationChange()));

    connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem *)),
            this,SLOT(slotCurrentItemChanged ( QTreeWidgetItem * , QTreeWidgetItem * )));

}


//Slot function implement
void DsSpriteTreeWidget::slotProjectInited()
{

    initView();             //check to destroy  all items in the tree for rebuilding
    createView();           //build the tree
}

void DsSpriteTreeWidget::slotCurProjectChange()
{
    if(m_changedCausedByView)
    {
        m_changedCausedByView = false;
        return ;
    }
    if(DsData::shareData()->getCurProject() == NULL)
    {
        return;
    }
    std::string curProjectName = DsData::shareData()->getCurProject()->getName();
    QList<QTreeWidgetItem* > itemList;
    itemList = this->findItems(s2q(curProjectName),Qt::MatchEndsWith|Qt::MatchCaseSensitive);
    //itemList = this->findItems("jump",Qt::MatchCaseSensitive);
    if(itemList.empty())
    {
        qDebug()<<"can't get the current project";
        return ;
    }

    qDebug()<<"itemList length is "<<QString::number(itemList.length());
    QList<QTreeWidgetItem* >::iterator iter;

    for(iter = itemList.begin();iter != itemList.end();iter++)
    {
        if((*iter)->text(0) == s2q(curProjectName))
        {
            qDebug()<<"get the current project";
            qDebug()<<(*iter)->text(0);

            m_changedCausedByDsData = true;
            this->setCurrentItem(*iter);
            break ;
        }
    }
    //this->updateView();
}

void DsSpriteTreeWidget::slotCurAnimationChange()
{
    if(m_changedCausedByView)
    {
        m_changedCausedByView =false;
        return ;
    }

    if(DsData::shareData()->getCurAnimation() == NULL)
    {
        return;
    }

    std::string curProjectName = DsData::shareData()->getCurProject()->getName();
    std::string curAnimationName = DsData::shareData()->getCurAnimation()->getName();

    QList<QTreeWidgetItem* > itemList;
    itemList = this->findItems(s2q(curProjectName),Qt::MatchEndsWith|Qt::MatchCaseSensitive);
    if(itemList.empty())
    {
        qDebug()<<"can't get the current Project name:"<<s2q(curProjectName);
        return ;
    }
    qDebug()<<"itemList length is "<<QString::number(itemList.length());
    QList<QTreeWidgetItem* >::iterator iter;
    QTreeWidgetItem* projectItem;

    //get project item
    for(iter = itemList.begin();iter != itemList.end();iter++)
    {
        if((*iter)->text(0) == s2q(curProjectName))
        {
            projectItem = (*iter);
            qDebug()<<"get the current Project item name:"<<s2q(curProjectName);
            break;
        }
    }

    //get child item(animation item) by parent item(project item)
    int i;
    QTreeWidgetItem* pItem;
    i = projectItem->childCount();
    if(0 >= i)
    {
        return;
    }
    for(int j=0;j<i;j++)
    {
        pItem = projectItem->child(j);
        if(pItem->text(0) == s2q(curAnimationName))
        {
            m_changedCausedByDsData = true;
            this->setCurrentItem(pItem);
            qDebug()<<"get the current animation item name:"<<s2q(curAnimationName);
            break;
        }
    }

   // this->updateView();
}

//When the Current Item of Tree is changed , update the corresponding data
void DsSpriteTreeWidget::slotCurrentItemChanged ( QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
    if(m_changedCausedByDsData)
    {
        m_changedCausedByDsData = false;
        return;
    }
    if(current == NULL)
    {
        return ;
    }

    qDebug()<<current->text(0);
    if(current->parent() == NULL)
    {
        qDebug()<<current->text(0)<<"has no parent";

        m_changedCausedByView = true;
        DsOperator::data.setCurProject(q2s(current->text(0)));
    }
    else
    {
       qDebug()<<current->text(0)<<"'s parent is "<<current->parent()->text(0);

       m_changedCausedByView = true;
       DsOperator::data.setCurProject(q2s(current->parent()->text(0)));

       m_changedCausedByView = true;
       DsOperator::data.setCurAnimation(q2s(current->text(0)));
    }
}

void DsSpriteTreeWidget::initView()
{

    int count = this->topLevelItemCount();
    qDebug()<<"topLevelItemCount = "<<QString::number(count);
    if(0==count)
    {
        return;
    }
    else
    {
        QTreeWidgetItem* item;
        QList<QTreeWidgetItem*> itemList;
        QList<QTreeWidgetItem*>::iterator iter;
        for(int j=0;j<count;j++)
        {
            item = this->takeTopLevelItem(0);
            int childNum = item->childCount();
            qDebug()<<"childNum = "<<QString::number(childNum);
            if(childNum <=0 )
            {
                continue;
            }
            itemList = item->takeChildren();
            qDebug()<<"itemList count = "<<QString::number(itemList.count());
            for(iter = itemList.begin(); iter != itemList.end();iter++)
            {
                qDebug()<<"destroy project"<<item->text(0)<<"'s animation:"<<(*iter)->text(0);
                delete (*iter);
            }

            qDebug()<<"destroy project:"<<item->text(0);
            delete item;
        }
    }
}

//When project data get ready, build the Tree Item
void DsSpriteTreeWidget::createView()
{
    int projectNum = 0;
    projectNum = DsData::shareData()->getProjectNu();

    if(0 >= projectNum)
    {
        return;
    }

    this->setColumnCount(1);
    this->setHeaderHidden(true);
   // m_spriteTreeWidget->setColumnHidden(2,true);

   // bool hasProject = false;
    bool hasCurProjet = false;
    bool hasCurAnimation = false;
    DsProject* curProject = s_shareData->getCurProject();
    if(curProject != NULL)
    {
        qDebug()<<"has current project";
        hasCurProjet = true;
    }

    DsAnimation* curAnimaton = s_shareData->getCurAnimation();
    if(curAnimaton != NULL)
    {
        qDebug()<<"has current animation";
        hasCurAnimation = true;
    }

    std::string curProjectName ;
    std::string curAnimatonName ;
    if(hasCurProjet)
    {
        curProjectName = curProject->getName();
    }
    if(hasCurAnimation)
    {
        curAnimatonName = curAnimaton->getName();
    }

   // rootItem->setIcon(0,QIcon(":/res/open.png"));

    QList<QTreeWidgetItem *> rootList;
   // rootList << rootItem;

   // this->insertTopLevelItems(0,rootList);

    //for iterator show project data
    DsProject* project;
    DsSprite* sprite;
    std::vector<DsAnimation*>::iterator anIter;
    std::vector<DsFrame*>::iterator frIter;

    std::string projectName;
    std::string spriteName;
    std::string animationName;
    //std::string frameName;
    QTreeWidgetItem* projectItem;
  //  QTreeWidgetItem* spriteItem;
    QTreeWidgetItem* animationItem;

    bool bSetCurrentItem = false;
    qDebug()<<"projectNum = "<<QString::number(projectNum);

    for(int i = 0 ; i <projectNum ;i++)
    {
        project = DsData::shareData()->getProject(i);
        assert(project != NULL);
        projectName = project->getName();

        projectItem = new QTreeWidgetItem(this,QStringList(s2q(projectName)));
        projectItem->setIcon(0,QIcon(DS_MS_TI_SPRITE));
        rootList << projectItem ;
        qDebug()<<"project"<<QString::number(i+1) <<" name = "<<s2q(projectName);

        sprite = project->getSprite();
        if(sprite == NULL)
            continue;

        /*
        qDebug()<<"project "<<s2q(projectName) <<" hsa sprite " <<s2q(projectName);

        spriteName = projectName;
        spriteItem = new QTreeWidgetItem(projectItem,QStringList(s2q(spriteName)));
        */
        if(!bSetCurrentItem)
        {
           if(!hasCurAnimation && hasCurProjet)
           {
               if(projectName == curProjectName)
               {
                    m_changedCausedByView = true;
                    this->setCurrentItem(animationItem);
                    bSetCurrentItem = true;
                }
           }
        }
        for(anIter = sprite->begin();anIter != sprite->end(); anIter++)
        {
            animationName = (*anIter)->getName();
            animationItem = new QTreeWidgetItem(projectItem,QStringList(s2q(animationName)));
            animationItem->setIcon(0,QIcon(DS_MS_TI_ANIMATION));
            projectItem->addChild(animationItem);
            if(!bSetCurrentItem)
            {
                if(hasCurProjet)
                {
                    if(projectName == curProjectName && animationName == curAnimatonName)
                    {
                         m_changedCausedByView = true;
                        this ->setCurrentItem(animationItem);
                        bSetCurrentItem = true;
                    }
                }
            }
        }//end for
    }//end for
    this->insertTopLevelItems(0,rootList);
}

//updateView
void DsSpriteTreeWidget::updateView()
{

}

//setCurProject
void DsSpriteTreeWidget::setCurProject(std::string projectName)
{
    DsData::shareData()->setCurProject(projectName);

}

//setCurAnimation
void DsSpriteTreeWidget::setCurAnimation(std::string animtionName)
{
     DsData::shareData()->setCurAnimation(animtionName);
}

//DsFrameTreeWidget
DsFrameTreeWidget::DsFrameTreeWidget(QWidget* parent)
    :QTreeWidget(parent)
{
    this->setColumnCount(1);
    this->setHeaderHidden(true);
}
