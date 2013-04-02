#include <assert.h>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include "DsSpriteDisplay.h"
#include <string>
#include <QDebug>

#include <QMainWindow>
#include <QVBoxLayout>
#include "operator/DsOperator.h"

#include "model/DsData.h"
#include "model/DsProject.h"
#include "model/DsSprite.h"
#include "model/DsAnimation.h"

#include "DsQrcMacros.h"


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

    //init menuAction type
    setActionTypeToNone();

    connectDsDataSignal();

    //just show the first col
    this->setColumnCount(2);
    this->setColumnHidden(1,true);
    this->setHeaderHidden(true);

    //only the DsSpriteTreeWidget had been built ,it's menus can create.
    createMultMenus();
}
void DsSpriteTreeWidget::connectDsDataSignal()
{
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
}
void DsSpriteTreeWidget::disconnectDsDataSignal()
{
    disconnect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
            this,SLOT(slotProjectInited()));
    disconnect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotProjectInited()));
    disconnect(DsData::shareData(),SIGNAL(signalCurSpriteChange()),
            this,SLOT(slotCurSpriteChange()));
    disconnect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotCurAnimationChange()));
    disconnect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem *)),
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

}
void DsSpriteTreeWidget::slotCurSpriteChange()
{

    if(DsData::shareData()->getCurSprite() == NULL)
    {
        return;
    }
    std::string curSpriteId = DsData::shareData()->getCurSprite()->getID();
    QList<QTreeWidgetItem* > itemList;
    itemList = this->findItems(s2q(curSpriteId),Qt::MatchEndsWith|Qt::MatchCaseSensitive,1);
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
            this->setCurrentItem(*iter);
            break ;
        }
    }
    itemList.clear();
}

void DsSpriteTreeWidget::slotCurAnimationChange()
{
    qDebug()<<"into slotCurAnimationChange";

    qDebug()<<s2q(DsData::shareData()->getCurAnimation()->getName());
    if(DsData::shareData()->getCurAnimation() == NULL)
    {
        return;
    }

    std::string curSpriteId = DsData::shareData()->getCurSprite()->getID();
    std::string curAnimationId = DsData::shareData()->getCurAnimation()->getID();
    QList<QTreeWidgetItem* > itemList;

    itemList = this->findItems(s2q(curSpriteId),Qt::MatchRecursive|Qt::MatchFixedString,1);
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
    itemList.clear();
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
            this->setCurrentItem(pItem);
            qDebug()<<"get the current animation item, Id is"<<s2q(curAnimationId);
            break;
        }
    }
}

//When the Current Item of Tree is changed , update the corresponding data
void DsSpriteTreeWidget::slotCurrentItemChanged ( QTreeWidgetItem * current, QTreeWidgetItem * previous)
{

    if(current == NULL)
    {
        return ;
    }

    qDebug()<<current->text(0);
    if(current->parent() == NULL)
    {
        qDebug()<<current->text(0)<<"projectItem has no parent";
    }
    else
    {
       qDebug()<<current->text(0)<<"'s parent is "<<current->parent()->text(0);

       if(current->parent()->parent() == NULL)
       {
           qDebug()<<"set current sprite :"<<current->text(0);
           DsOperator::data()->setCurSprite(q2s(current->text(1)));
       }
       else
       {
           DsOperator::data()->setCurSprite(q2s(current->parent()->text(1)));
           DsOperator::data()->setCurAnimation(q2s(current->text(1)));
           qDebug()<<"set current animation : "<<current->text(0);
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
    QStringList projectItemList;
    projectItemList<<s2q(projectName)<<"1";
    QTreeWidgetItem* projectItem = new QTreeWidgetItem(this,projectItemList);
    projectItemList.clear();

    projectItem->setIcon(0,QIcon(DS_ICON_PRO_PROJECT));         //will send itemChanged signal
    rootList<<projectItem;
    DsSprite* sprite;

    std::vector<DsAnimation*>::iterator anIter;
    std::string spriteName;
    std::string spriteId;
    std::string animationName;
    std::string animationId;
    QTreeWidgetItem* spriteItem;
    QTreeWidgetItem* animationItem;
    QStringList spriteItemList;
    QStringList animationItemList;
    bool bSetCurrentItem = false;

    disconnectDsDataSignal();          //disconnect signal ,avoid  sending signal again
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
        spriteItem->setIcon(0,QIcon(DS_ICON_PRO_SPRITE));
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
                    this->setCurrentItem(spriteItem);
                    this->expandItem(spriteItem);           //expand by default
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
            animationItem->setIcon(0,QIcon(DS_ICON_PRO_ANIMATION));
            animationItem->setFlags(Qt::ItemIsEditable|animationItem->flags());
            qDebug()<<"animationItem Flags="<<QString::number(animationItem->flags());

            spriteItem->addChild(animationItem);
            if(!bSetCurrentItem)
            {
                if(hasCurSprite)
                {
                    if(spriteName == curSpriteName && animationName == curAnimationName)
                    {
                        this ->setCurrentItem(animationItem);
                        bSetCurrentItem = true;
                    }
                }
            }
        }//end for
    }//end for
    connectDsDataSignal();
    if(bSetCurrentItem == false)
    {
        this->expandItem(projectItem);
    }
    this->insertTopLevelItems(0,rootList);

}

//==========================================================================

//RightButton clicked contextMenuEvent be called
void DsSpriteTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    int anim_play=DsOperator::animation()->isAnimationPlay();
    if(anim_play)
    {
        m_newProject->setDisabled(true);
        m_openProject->setDisabled(true);
        m_addSprite->setDisabled(true);
        m_save->setDisabled(true);
        m_close->setDisabled(true);
        m_addAnimation->setDisabled(true);
        m_removeSprite->setDisabled(true);
        m_renameSprite->setDisabled(true);
        m_exportSprite->setDisabled(true);
        m_removeAnimation->setDisabled(true);
        m_renameAnimation->setDisabled(true);
    }
    else
    {
        m_newProject->setEnabled(true);
        m_openProject->setEnabled(true);
        m_addSprite->setEnabled(true);
        m_save->setEnabled(true);
        m_close->setEnabled(true);
        m_addAnimation->setEnabled(true);
        m_removeSprite->setEnabled(true);
        m_renameSprite->setEnabled(true);
        m_exportSprite->setEnabled(true);
        m_removeAnimation->setEnabled(true);
        m_renameAnimation->setEnabled(true);
    }

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
            qDebug()<<"show m_projectMenus";
            m_projectMenus->popup(QCursor::pos());
        }
        else
        {
            if(item->parent()->parent() == NULL)
            {
               qDebug()<<"show m_spriteMenus";
                m_spriteMenus->popup(QCursor::pos());
            }
            else
            {
                qDebug()<<"clicked item:"<<item->text(0);
               // qDebug()<<item->parent()->text(0);
                qDebug()<<"show m_animationMenus";
                m_animationMenus->popup(QCursor::pos());
            }
        }
    }
}

void DsSpriteTreeWidget::createMultMenus()
{

    createBlankMenus();
    createProjectMenus();
    createSpriteMenus();
    createAnimationMenus();

    connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this,SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem* , int)),
            this,SLOT(slotItemDoubleClicked(QTreeWidgetItem * ,int)));

}

void DsSpriteTreeWidget::createBlankMenus()
{
    m_blankMenus = new QMenu(this);
    m_newProject = m_blankMenus->addAction(tr("New project"));
    m_openProject = m_blankMenus->addAction(tr("Open project"));
    connect(m_newProject,SIGNAL(triggered()),this,SLOT(slotNewProject()));
    connect(m_openProject,SIGNAL(triggered()),this,SLOT(slotOpenProject()));
}

void DsSpriteTreeWidget::createProjectMenus()
{
    m_projectMenus = new QMenu(this);
    m_addSprite = m_projectMenus->addAction(tr("Add sprite"));
    m_save = m_projectMenus->addAction(tr("Save"));
    m_close = m_projectMenus->addAction(tr("Close"));

    connect(m_addSprite,SIGNAL(triggered()),this,SLOT(slotAddSprite()));
    connect(m_save,SIGNAL(triggered()),this,SLOT(slotSaveProject()));
    connect(m_close,SIGNAL(triggered()),this,SLOT(slotCloseProject()));

}
void DsSpriteTreeWidget::createSpriteMenus()
{
    m_spriteMenus = new QMenu(this);
    m_addAnimation = m_spriteMenus->addAction(tr("Add animation"));
    m_removeSprite = m_spriteMenus->addAction(tr("Remove sprite"));
    m_renameSprite = m_spriteMenus->addAction(tr("Rename sprite"));
    m_exportSprite = m_spriteMenus->addAction(tr("Export sprite"));

    connect(m_addAnimation,SIGNAL(triggered()),this,SLOT(slotAddAnimation()));
    connect(m_removeSprite,SIGNAL(triggered()),this,SLOT(slotRemoveSprite()));
    connect(m_renameSprite,SIGNAL(triggered()),this,SLOT(slotRenameSprite()));
    connect(m_exportSprite,SIGNAL(triggered()),this,SLOT(slotExportSprite()));
}

void DsSpriteTreeWidget::createAnimationMenus()
{
    m_animationMenus = new QMenu(this);
    m_renameAnimation = m_animationMenus->addAction(tr("Rename animation"));
    m_removeAnimation = m_animationMenus->addAction(tr("Remove animation"));

    connect(m_renameAnimation,SIGNAL(triggered()),this,SLOT(slotRenameAnimation()));
    connect(m_removeAnimation,SIGNAL(triggered()),this,SLOT(slotRemoveAnimation()));

}


/* Blank menus slots  */
void DsSpriteTreeWidget::slotNewProject()
{
    DsOperator::io()->newProject();
}
void DsSpriteTreeWidget::slotOpenProject()
{
     DsOperator::io()->loadProject();
}

/* Project menus slots  */
void DsSpriteTreeWidget::slotAddSprite()
{
    QTreeWidgetItem *  currentItem = this->currentItem();
    assert(currentItem != NULL);
    qDebug()<<"add sprite to project :"<<currentItem->text(0);
    DsOperator::data()->newSprite();
}
void DsSpriteTreeWidget::slotSaveProject()
{
    m_actionType = MENUS_ACT_SAVE_PROJECT;
    DsOperator::io()->saveProject();
}
void DsSpriteTreeWidget::slotCloseProject()
{
    DsOperator::io()->closeProject();
}

/* Sprite menus slots  */
void DsSpriteTreeWidget::slotAddAnimation()
{
    QTreeWidgetItem *  currentItem = this->currentItem();
    assert(currentItem != NULL);
    qDebug()<<"add animation to sprite :"<<currentItem->text(0);
    DsOperator::data()->newAnimation();
}

void DsSpriteTreeWidget::slotRemoveSprite()
{
    QTreeWidgetItem *  currentItem = this->currentItem();
    assert(currentItem != NULL);
    m_actionType = MENUS_ACT_REMOVE_SPRITE;
    qDebug()<<"remove sprite :"<<currentItem->text(0);
    DsOperator::data()->removeSprite(q2s(currentItem->text(1)));
}

void DsSpriteTreeWidget::slotRenameSprite()
{
    QTreeWidgetItem *  currentItem = this->currentItem();
    assert(currentItem != NULL);
    m_actionType = MENUS_ACT_RENAME_SPRITE;
    if(currentItem->flags() & (Qt::ItemIsEditable))
    {
        originalName = currentItem->text(0);
        this->editItem(currentItem, 0);
        qDebug()<<"About to rename sprite:"<<originalName;
    }
}

void DsSpriteTreeWidget::slotExportSprite()
{
    QTreeWidgetItem *  currentItem = this->currentItem();
    assert(currentItem != NULL);
    DsOperator::io()->exportFSprite(q2s(currentItem->text(1)));
}

/* Animation menus slots  */
void DsSpriteTreeWidget::slotRenameAnimation()
{

    QTreeWidgetItem *  currentItem = this->currentItem();
    assert(currentItem != NULL);
    m_actionType = MENUS_ACT_RENAME_ANIMATION;
    if(currentItem->flags() & (Qt::ItemIsEditable))
    {
        originalName = currentItem->text(0);
        this->editItem(currentItem, 0);
        qDebug()<<"About to rename animation:"<<originalName;
    }
    else
    {
        QMessageBox::information(this,tr("Entry Rename Animation"),tr("this item can not edit"));
    }
}

void DsSpriteTreeWidget::slotRemoveAnimation()
{
    QTreeWidgetItem *  currentItem = this->currentItem();
    assert(currentItem != NULL);
    m_actionType = MENUS_ACT_REMOVE_ANIMATION;
    qDebug()<<"remove animation :"<<currentItem->text(0);
    DsOperator::data()->removeAnimation(q2s(currentItem->text(1)));
}

void DsSpriteTreeWidget::slotItemChanged(QTreeWidgetItem * item, int column)
{
    //qDebug()<<"try to rename sprite: "<<originalName<<" to "<<item->text(0);
   if(m_actionType != MENUS_ACT_RENAME_ANIMATION &&
      m_actionType != MENUS_ACT_RENAME_SPRITE)
    {
        return;
    }
    setActionTypeToNone();
    bool bRename;
    if(item->parent() == NULL)
    {
        qDebug()<<"rename project "<<item->text(0);
    }
    else
    {
        if(item->parent()->parent() == NULL)
        {
            //sprite item
            qDebug()<<"try to rename sprite: "<<originalName<<" to "<<item->text(0);
            disconnect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
                    this,SLOT(slotProjectInited()));
            bRename = DsOperator::data()->renameSprite(
                            q2s(item->text(1)),
                            q2s(item->text(0))
                            );
            connect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
                    this,SLOT(slotProjectInited()));
            if(!bRename)
            {
                qDebug()<<"can not rename sprite";
                disconnect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                        this,SLOT(slotItemChanged(QTreeWidgetItem*,int)));
                item->setText(0,originalName);
                connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                        this,SLOT(slotItemChanged(QTreeWidgetItem*,int)));
            }
            else
            {
                qDebug()<<"rename sprite in project "<<item->parent()->text(0)
                       <<" from "<<originalName<<" to "<<item->text(0);
            }
        }
        else
        {
            //animation item
            qDebug()<<"try to rename animation: "<<originalName<<" to "<<item->text(0);
            disconnect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
                    this,SLOT(slotProjectInited()));
            bRename = DsOperator::data()->renameAnimation(
                            q2s(item->parent()->text(1)),
                            q2s(item->text(1)),
                            q2s(item->text(0))
                            );
            connect(DsData::shareData(),SIGNAL(signalProjectPropertyChange()),
                    this,SLOT(slotProjectInited()));
            if(!bRename)
            {
                qDebug()<<"can not rename animation";
                disconnect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                        this,SLOT(slotItemChanged(QTreeWidgetItem*,int)));
                item->setText(0,originalName);
                connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                        this,SLOT(slotItemChanged(QTreeWidgetItem*,int)));
            }
            else
            {
                qDebug()<<"rename animation in sprite "<<item->parent()->text(0)
                       <<" from "<<originalName<<" to "<<item->text(0);
            }
        }
    }
}

void DsSpriteTreeWidget::slotItemDoubleClicked(QTreeWidgetItem * item, int column)
{

    if(item->parent() == NULL)
    {
        qDebug()<<"in slotItemDoubleClicked";
    }
    else
    {
        //sprite item
        if(item->parent()->parent() == NULL)
        {
            //sprite item
            m_actionType = MENUS_ACT_RENAME_SPRITE;
            if(item->flags() & (Qt::ItemIsEditable))
            {
                originalName = item->text(0);
                this->editItem(item, 0);
                qDebug()<<"in double key About to rename sprite:"<<originalName;
            }
        }
        else
        {
            //animation item
            m_actionType =MENUS_ACT_RENAME_ANIMATION;
            if(item->flags() & (Qt::ItemIsEditable))
            {
                originalName = item->text(0);
                this->editItem(item, 0);
                qDebug()<<"in double key About to rename animation:"<<originalName;
            }
        }

    }

}

//==========================================================================
//DsFrameTreeWidget
DsFrameTreeWidget::DsFrameTreeWidget(QWidget* parent)
    :QTreeWidget(parent)
{

    //sigal from DsData
    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurSpriteChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameImageChange()),
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
    connect(DsData::shareData(),SIGNAL(signalCurProjectChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurSpriteChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurAnimationChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameChange()),
            this,SLOT(slotProjectRefresh()));
    connect(DsData::shareData(),SIGNAL(signalCurFrameImageChange()),
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

