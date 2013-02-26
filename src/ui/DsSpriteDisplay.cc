#include <assert.h>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include "DsSpriteDisplay.h"
#include <string>
#include <QDebug>

#include <QMainWindow>
#include <QVBoxLayout>
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
    return s.toStdString();
}


DsSpriteDisplay::DsSpriteDisplay(QWidget* parent)
    :QWidget(parent)
{
/*
    //add Dock to MainWindow
    m_Dock = new QDockWidget(tr("SpriteDisplay"),parent);
    m_Dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_Dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    m_Dock->setWindowTitle("");

    //add tabWidget to Dock
    m_tabWidget = new QTabWidget(m_Dock);
    m_Dock->setWidget(m_tabWidget);

    //add spriteTreeWidget to tabWidget
    m_spriteTreeWidget = new DsSpriteTreeWidget(m_tabWidget);
    m_frameTreeWidget = new DsFrameTreeWidget(m_tabWidget);

    m_tabWidget->addTab(m_spriteTreeWidget,tr("Sprite"));
    m_tabWidget->addTab(m_frameTreeWidget,tr("Frame"));

    QMainWindow* MainWindow = (QMainWindow*)parent->parent();
    MainWindow->addDockWidget(Qt::RightDockWidgetArea, m_Dock);
*/
    m_tabWidget = new QTabWidget;

    QVBoxLayout* vLayout = new QVBoxLayout;
    m_spriteTreeWidget = new DsSpriteTreeWidget(m_tabWidget);
    m_frameTreeWidget = new DsFrameTreeWidget(m_tabWidget);

    m_tabWidget->addTab(m_spriteTreeWidget,tr("Sprite"));
    m_tabWidget->addTab(m_frameTreeWidget,tr("Frame"));
    vLayout->addWidget(m_tabWidget);
    setLayout(vLayout);

}


//DsSpriteTreeWidget
DsSpriteTreeWidget::DsSpriteTreeWidget(QWidget* parent)
    :QTreeWidget(parent)
{
    m_changedCausedByDsData = true;
    m_changedCausedByView = false;
    m_markCurProjectChange = false;

  //  connect(DsData::shareData(),SIGNAL(signalDataPropertyChange()),
    //        this,SLOT(slotProjectInited()));

    connect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
            this,SLOT(slotProjectInited()));

    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotProjectInited()));

    connect(DsData::shareData(),SIGNAL(signalCurSpriteChange()),
            this,SLOT(slotCurSpriteChange()));

    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotCurAnimationChange()));

    connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem *)),
            this,SLOT(slotCurrentItemChanged ( QTreeWidgetItem * , QTreeWidgetItem * )));


    //just show the first col
    this->setColumnCount(1);
    this->setHeaderHidden(true);

    //only the DsSpriteTreeWidget had been built ,it's menus can create.
    createMultMenus();
}

//Slot function implement
void DsSpriteTreeWidget::slotProjectInited()
{

    initView();             //check to destroy  all items in the tree for rebuilding
    createView();           //build the tree
}

void DsSpriteTreeWidget::slotCurProjectChange()
{
    /*
    if(m_changedCausedByView)
    {
        m_changedCausedByView = false;
        return ;
    }
    if(DsData::shareData()->getProject() == NULL)
    {
        return;
    }
    std::string curProjectName = DsData::shareData()->getProject()->getName();
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
    */
    //this->updateView();
}
void DsSpriteTreeWidget::slotCurSpriteChange()
{
    if(m_changedCausedByView)
    {
        m_changedCausedByView = false;
        return ;
    }
    if(DsData::shareData()->getCurSprite() == NULL)
    {
        return;
    }
    std::string curSpriteId = DsData::shareData()->getCurSprite()->getID();
    QList<QTreeWidgetItem* > itemList;
    itemList = this->findItems(s2q(curSpriteId),Qt::MatchEndsWith|Qt::MatchCaseSensitive,1);
    //itemList = this->findItems("jump",Qt::MatchCaseSensitive);
    if(itemList.empty())
    {
        qDebug()<<"can't get the current sprite ID";
        return ;
    }

    qDebug()<<"itemList length is "<<QString::number(itemList.length());
    QList<QTreeWidgetItem* >::iterator iter;

    for(iter = itemList.begin();iter != itemList.end();iter++)
    {
        if((*iter)->text(1) == s2q(curSpriteId))
        {
            qDebug()<<"get the current sprite";
            qDebug()<<(*iter)->text(0);

            m_changedCausedByDsData = true;
            this->setCurrentItem(*iter);
            break ;
        }
    }
}

void DsSpriteTreeWidget::slotCurAnimationChange()
{
    if(m_changedCausedByView)
    {
        m_changedCausedByView = false;
        return ;
    }

    if(DsData::shareData()->getCurAnimation() == NULL)
    {
        return;
    }

    std::string curSpriteId = DsData::shareData()->getCurSprite()->getID();
    std::string curAnimationId = DsData::shareData()->getCurAnimation()->getID();

    QList<QTreeWidgetItem* > itemList;
    itemList = this->findItems(s2q(curSpriteId),Qt::MatchEndsWith|Qt::MatchCaseSensitive);
    if(itemList.empty())
    {
        qDebug()<<"can't get the current sprite ID:"<<s2q(curSpriteId);
        return ;
    }
    qDebug()<<"itemList length is "<<QString::number(itemList.length());
    QList<QTreeWidgetItem* >::iterator iter;
    QTreeWidgetItem* spriteItem;

    //get sprite item
    for(iter = itemList.begin();iter != itemList.end();iter++)
    {
        if((*iter)->text(1) == s2q(curSpriteId))
        {
            spriteItem = (*iter);
            qDebug()<<"get the current sprite item, Id is "<<s2q(curSpriteId);
            break;
        }
    }

    //get child item(animation item) by parent item(sprite item)
    int i;
    QTreeWidgetItem* pItem;
    i = spriteItem->childCount();
    if(0 >= i)
    {
        return;
    }
    for(int j=0;j<i;j++)
    {
        pItem = spriteItem->child(j);
        if(pItem->text(1) == s2q(curAnimationId))
        {
            m_changedCausedByDsData = true;
            this->setCurrentItem(pItem);
            qDebug()<<"get the current animation item, Id is"<<s2q(curAnimationId);
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
        qDebug()<<current->text(0)<<"projectItem has no parent";

      //  m_changedCausedByView = true;
      //  DsOperator::data.setCurProject(q2s(current->text(0)));
    }
    else
    {
       qDebug()<<current->text(0)<<"'s parent is "<<current->parent()->text(0);

       if(current->parent()->parent() == NULL)
       {
           qDebug()<<"set current sprite ,ID is "<<current->text(1);

           m_changedCausedByView = true;
           DsOperator::data()->setCurSprite(q2s(current->text(1)));
       }
       else
       {
           m_changedCausedByView = true;
           DsOperator::data()->setCurSprite(q2s(current->parent()->text(1)));
           m_changedCausedByView = true;
           DsOperator::data()->setCurAnimation(q2s(current->text(1)));

       }
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
        this->clear();
    }
    /*
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
    }*/
}

//When project data get ready, build the Tree Item
void DsSpriteTreeWidget::createView()
{

    DsProject* pro = DsData::shareData()->getProject();
    if(pro == NULL)
    {
        qDebug()<<"has no current project";
        return;
    }

    int spriteNum = pro->getSpriteNu();

    qDebug()<<"spriteNum = "<<QString::number(spriteNum);

    bool hasCurSprite = false;
    bool hasCurAnimation = false;
    DsSprite* pCurSprite;
    DsAnimation* pCurAnimation;

    pCurSprite = DsData::shareData()->getCurSprite();
    if(pCurSprite != NULL)
    {
        qDebug()<<"has current sprite";
        hasCurSprite = true;
    }

    pCurAnimation = DsData::shareData()->getCurAnimation();
    if(pCurAnimation != NULL)
    {
        qDebug()<<"has current animation";
        hasCurAnimation = true;
    }


    std::string curSpriteName ;
    std::string curAnimationName;
    if(hasCurSprite)
    {
        curSpriteName = pCurSprite->getName();
    }
    if(hasCurAnimation)
    {
        curAnimationName = pCurAnimation->getName();
    }


    QList<QTreeWidgetItem *> rootList;
    std::string projectName = pro->getFileName();
    QTreeWidgetItem* projectItem = new QTreeWidgetItem(this,QStringList(s2q(projectName)));
    rootList<<projectItem;
    DsSprite* sprite;
  //  DsAnimation* animation;

    std::vector<DsAnimation*>::iterator anIter;
    std::vector<DsSprite*>::iterator sprIter;


    std::string spriteName;
    std::string spriteId;
    std::string animationName;
    std::string animationId;
    QTreeWidgetItem* spriteItem;
    QTreeWidgetItem* animationItem;
    QStringList spriteItemList;
    QStringList animationItemList;
    bool bSetCurrentItem = false;

    for(int i = 0 ; i <spriteNum ;i++)
    {
        sprite = pro->getSprite(i);

        assert(sprite != NULL);
        spriteName = sprite->getName();
        spriteId = sprite->getID();

        qDebug()<<"spriteName"<<s2q(spriteName);
        qDebug()<<"spriteId"<<s2q(spriteId);
        spriteItemList<<s2q(spriteName)<<s2q(spriteId);
        spriteItem = new QTreeWidgetItem(projectItem,spriteItemList);
        spriteItemList.clear();
        spriteItem->setIcon(0,QIcon(DS_MS_TI_SPRITE));
        spriteItem->setFlags(spriteItem->flags()|Qt::ItemIsEditable);
        qDebug()<<"spriteItem Flags="<<QString::number(spriteItem->flags());
        projectItem->addChild(spriteItem);
        qDebug()<<"sprite"<<QString::number(i+1) <<" name = "<<s2q(spriteName);

        if(!bSetCurrentItem)
        {
           if(!hasCurAnimation && hasCurSprite)
           {
               if(spriteName == curSpriteName)
               {
                    m_changedCausedByView = true;
                    this->setCurrentItem(spriteItem);
                    bSetCurrentItem = true;
                }
           }
        }
        for(anIter = sprite->begin();anIter != sprite->end(); anIter++)
        {
            animationName = (*anIter)->getName();
            animationId = (*anIter)->getID();
            animationItemList<<s2q(animationName)<<s2q(animationId);
            animationItem = new QTreeWidgetItem(spriteItem,animationItemList);
            animationItemList.clear();
            animationItem->setIcon(0,QIcon(DS_MS_TI_ANIMATION));
            animationItem->setFlags(Qt::ItemIsEditable|animationItem->flags());
            qDebug()<<"animationItem Flags="<<QString::number(animationItem->flags());

            spriteItem->addChild(animationItem);
            if(!bSetCurrentItem)
            {
                if(hasCurSprite)
                {
                    if(spriteName == curSpriteName && animationName == curAnimationName)
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


    //===========================
    /*int projectNum = 0;
    projectNum = DsData::shareData()->getProjectNu();

    if(0 >= projectNum)
    {
        return;
    }
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

    QList<QTreeWidgetItem *> rootList;
    DsProject* project;
    DsSprite* sprite;
    std::vector<DsAnimation*>::iterator anIter;
    std::vector<DsFrame*>::iterator frIter;

    std::string projectName;
    std::string animationName;
    QTreeWidgetItem* projectItem;

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
        projectItem->setFlags(projectItem->flags()|Qt::ItemIsEditable);
        qDebug()<<"projectItem Flags="<<QString::number(projectItem->flags());
        rootList << projectItem ;
        qDebug()<<"project"<<QString::number(i+1) <<" name = "<<s2q(projectName);

        sprite = project->getSprite();
        if(sprite == NULL)
        {
            continue;
        }

        if(!bSetCurrentItem)
        {
           if(!hasCurAnimation && hasCurProjet)
           {
               if(projectName == curProjectName)
               {
                    m_changedCausedByView = true;
                    this->setCurrentItem(projectItem);
                    bSetCurrentItem = true;
                }
           }
        }
        for(anIter = sprite->begin();anIter != sprite->end(); anIter++)
        {
            animationName = (*anIter)->getName();
            animationItem = new QTreeWidgetItem(projectItem,QStringList(s2q(animationName)));
            animationItem->setIcon(0,QIcon(DS_MS_TI_ANIMATION));
            animationItem->setFlags(Qt::ItemIsEditable|animationItem->flags());
            qDebug()<<"animationItem Flags="<<QString::number(animationItem->flags());

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
    */
}

//updateView
void DsSpriteTreeWidget::updateView()
{

}

//setCurProject
void DsSpriteTreeWidget::setCurProject(std::string projectName)
{
    //DsData::shareData()->setCurProject(projectName);

}




//setCurAnimation
void DsSpriteTreeWidget::setCurAnimation(std::string animtionName)
{
    // DsData::shareData()->setCurAnimation(animtionName);
}

//==========================================================================

//RightButton clicked contextMenuEvent be called
void DsSpriteTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{

   QTreeWidgetItem* item = this->itemAt(mapFromGlobal(QCursor::pos()));
    if(item == NULL)
    {
        qDebug()<<"show m_blankMenus";
        m_blankMenus->popup(QCursor::pos());
    }
    else
    {
         qDebug()<<"not show m_blankMenus";
        if(item->parent() == NULL)
        {
            qDebug()<<"this item no parent";
            qDebug()<<"show m_spriteMenus";
            m_spriteMenus->popup(QCursor::pos());
        }
        else
        {
             qDebug()<<"clicked item:"<<item->text(0);
             qDebug()<<item->parent()->text(0);
             qDebug()<<"show m_animationMenus";
             m_animationMenus->popup(QCursor::pos());
             //m_animationMenus->exec(QCursor::pos());
        }
    }

}

void DsSpriteTreeWidget::createMultMenus()
{

    createBlankMenus();
    createSpriteMenus();
    createAnimationMenus();

}

void DsSpriteTreeWidget::createBlankMenus()
{
    m_blankMenus = new QMenu(this);
    m_addSprite = m_blankMenus->addAction(tr("Add sprite"));
    m_openSprite = m_blankMenus->addAction(tr("Open sprite"));

    connect(m_addSprite,SIGNAL(triggered()),this,SLOT(slotAddSprite()));
    connect(m_openSprite,SIGNAL(triggered()),this,SLOT(slotOpenSprite()));
}

void DsSpriteTreeWidget::createSpriteMenus()
{
    m_spriteMenus = new QMenu(this);
    m_addAnimation  = m_spriteMenus->addAction(tr("Add animation"));
    m_closeSprite = m_spriteMenus->addAction(tr("Close sprite"));
    m_renameSprite = m_spriteMenus->addAction(tr("Rename sprite"));

    connect(m_addAnimation,SIGNAL(triggered()),this,SLOT(slotAddAnimation()));
    connect(m_closeSprite,SIGNAL(triggered()),this,SLOT(slotCloseSprite()));
    connect(m_renameSprite,SIGNAL(triggered()),this,SLOT(slotRenameSprite()));

}

void DsSpriteTreeWidget::createAnimationMenus()
{
    m_animationMenus = new QMenu(this);
    m_renameAnimation = m_animationMenus->addAction(tr("Rename animation"));
    m_deleteAnimation = m_animationMenus->addAction(tr("Delete animation"));

    connect(m_renameAnimation,SIGNAL(triggered()),this,SLOT(slotRenameAnimation()));
    connect(m_deleteAnimation,SIGNAL(triggered()),this,SLOT(slotDeleteAnimation()));

}


/* Blank menus slots  */
void DsSpriteTreeWidget::slotAddSprite()
{
    QMessageBox::information(this,tr("slotAddSprite"),tr("Add sprite"));
}

void DsSpriteTreeWidget::slotOpenSprite()
{
    QMessageBox::information(this,tr("slotOpenSprite"),tr("Open sprite"));
}


/* Sprite menus slots  */
void DsSpriteTreeWidget::slotAddAnimation()
{
    QMessageBox::information(this,tr("slotAddAnimation"),tr("Add animation"));
}

void DsSpriteTreeWidget::slotCloseSprite()
{
    QMessageBox::information(this,tr("slotCloseSprite"),tr("Close sprite"));
}

void DsSpriteTreeWidget::slotRenameSprite()
{
    QMessageBox::information(this,tr("slotRenameSprite"),tr("Rename sprite"));
}



/* Animation menus slots  */
void DsSpriteTreeWidget::slotRenameAnimation()
{
    QMessageBox::information(this,tr("Entry Rename Animation"),tr("Rename animation"));
    QTreeWidgetItem *  currentItem = this->currentItem();
    if(currentItem->flags() & (Qt::ItemIsEditable))
    {
           this->editItem(currentItem, 0);
    }
    else
    {
        QMessageBox::information(this,tr("Entry Rename Animation"),tr("this item can not edit"));
    }

}

void DsSpriteTreeWidget::slotDeleteAnimation()
{
    QMessageBox::information(this,tr("Remove Animation"),tr("Remove animation"));
}



//==========================================================================
//DsFrameTreeWidget
DsFrameTreeWidget::DsFrameTreeWidget(QWidget* parent)
    :QTreeWidget(parent)
{

    //sigal from DsData
    connect(DsData::shareData(),SIGNAL(signalDataPropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurSpriteChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalAnimationPropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalFramePropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalFrameImagePropertyChange()),
            this,SLOT(slotProjectRefresh()));

    //sigal from this
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem* ,int )),
            this,SLOT(slotItemClicked(QTreeWidgetItem* ,int )));


    /*
    connect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
            this,SLOT(slotProjectInited()));

    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotCurProjectChange()));

    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotCurAnimationChange()));

    connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem *)),
            this,SLOT(slotCurrentItemChanged ( QTreeWidgetItem * , QTreeWidgetItem * )));

*/
    //just show the first col
    this->setColumnCount(1);
    this->setHeaderHidden(true);
}


void DsFrameTreeWidget::initView()
{
    int count = this->topLevelItemCount();
    qDebug()<<"topLevelItemCount = "<<QString::number(count);
    if(0==count)
    {
        return;
    }
    else
    {
        this->clear();
    }
}

void DsFrameTreeWidget::createView()
{

    qDebug()<<"in frameTreewidget::createView";
    DsFrame* curFrame = DsData::shareData()->getCurFrame();
    if(curFrame == NULL)
    {
        return;
    }
    if(curFrame->getType() == DsFrame::FRAME_TWEEN)
    {
        return;
    }
    int imageNum = ((DsKeyFrame*)curFrame)->getFrameImageNu();
    if(imageNum == 0)
    {
        return ;
    }

    qDebug()<<"curFrame image num = "<<QString::number(imageNum);
    QList<QTreeWidgetItem* > itemList;
    QTreeWidgetItem* iamgeItem;
    DsFrameImage* frameImage;
    DsImage* image;

    std::string frameImageId;
    std::string imageName;
    QStringList stringList;

    std::string pathName;
    std::string path;
    std::string fileName;
    int index;
    for(int i=0;i<imageNum;i++)
    {
        frameImage = ((DsKeyFrame*)curFrame)->getFrameImage(i);

        image = frameImage->getImage();
        frameImageId = frameImage->getID();
        imageName = image->name;
        pathName = frameImage->getImage()->name;

        index = pathName.find_last_of("/\\");
        qDebug()<<"find_last_of '\' index = "<<QString::number(index);
        if(-1 == index)
        {
            fileName = pathName;
        }
        else
        {
            fileName = pathName.substr(index+1);
        }

        stringList<< s2q(fileName)<<s2q(frameImageId);
        iamgeItem = new QTreeWidgetItem(this,stringList);
        stringList.clear();
        iamgeItem->setIcon(0,QIcon(s2q(pathName)));

    }
    this->insertTopLevelItems(0,itemList);
}

//slot
void DsFrameTreeWidget::slotProjectRefresh()
{
   initView();
   createView();
}

void DsFrameTreeWidget::slotItemClicked(QTreeWidgetItem* item,int column)
{

    QString name = item->text(1);


    disconnect(DsData::shareData(),0,this,0);
    qDebug()<<"call setCurFrameImage name = "<<name;
    DsOperator::data()->setCurFrameImage(q2s(name));

    //sigal from DsData
    connect(DsData::shareData(),SIGNAL(signalDataPropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurSpriteChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameChange()),
            this,SLOT(slotProjectRefresh()));

    connect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalAnimationPropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalFramePropertyChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalFrameImagePropertyChange()),
            this,SLOT(slotProjectRefresh()));

}

