#include <string.h>
#include "DsQrcMacros.h"
#include "DsResourceDisplay.h"
#include "src/model/DsData.h"
#include "src/model/DsProject.h"

extern DsData* s_shareData;

DsResourceDisplay::DsResourceDisplay(QWidget* p)
    :QWidget(p)
{
    // 加一个右键菜单
    m_menu = new QMenu(this);
    m_flushAction = m_menu->addAction(tr("refresh"));
    connect(m_flushAction, SIGNAL(triggered()), this, SLOT(refreshFolder()));


    m_tree = new QTreeWidget;
    m_tree->setColumnCount(1);
    m_tree->setHeaderLabel("Path");
    m_tree->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    connect(m_tree, SIGNAL(clicked(const QModelIndex &)), this, SLOT(selectSomething()));
    connect(m_tree, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(expandSomething(QTreeWidgetItem *)));
    connect(m_tree, SIGNAL(itemCollapsed (QTreeWidgetItem *)), this, SLOT(unExpandSomething(QTreeWidgetItem *)));

    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addWidget(m_tree);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout, 0);
    setLayout(mainLayout);

    connect(DsData::shareData(), SIGNAL(signalCurProjectChange()), this, SLOT(refreshFolder()));
}

void DsResourceDisplay::addResFolder(QString strPath, QString itemName)
{
    if (!strPath.isNull()) // user choiced folder
    {
        if (strPath.right(1) != QString('/'))
        {
            strPath += '/';
        }
        QTreeWidgetItem *noteTemp = new QTreeWidgetItem();
        noteTemp->setText(0, itemName);
        noteTemp->setIcon(0, QIcon(DS_FB_FILE));
        m_tree->addTopLevelItem(noteTemp);
        addFileItem(strPath, noteTemp);
    }
}

void DsResourceDisplay::selectSomething() // 点击图片图标，返回路径和文件名
{
    int num = m_tree->currentItem()->childCount();
    if (num == 0)
    {
        QString dirTemp;
        QString fileName;

        fileName = m_tree->currentItem()->text(0);

        if(fileName.right(4).compare(".jpg", Qt::CaseInsensitive) == 0 ||
                fileName.right(4).compare(".bmp", Qt::CaseInsensitive) == 0 ||
                fileName.right(4).compare(".tag", Qt::CaseInsensitive) == 0 ||
                fileName.right(4).compare(".png", Qt::CaseInsensitive) == 0)
        {

            dirTemp = getParentDirFromItem(m_tree->currentItem());
            std::string path(qPrintable(dirTemp));
            std::string filename(qPrintable(fileName));
            emit resFileSelect(path, filename);
        }
    }
}

void DsResourceDisplay::expandSomething(QTreeWidgetItem *treeItem)
{
    QTreeWidgetItem *currentTree = treeItem;
    int nchildCount = currentTree->childCount();

    if (nchildCount > 0) // 貌似能展开都不会为0
    {
        QString strfileName;
        // 先遍历这个Item为路径是否有文件夹，若有则添加
        QString dirCurrent = getDirFromItem(currentTree);
        for (int i = 0; i < nchildCount; ++i)
        {
            strfileName = currentTree->child(i)->text(0);

            if (strfileName.right(4).compare(".jpg", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".bmp", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".tag", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".png", Qt::CaseInsensitive) == 0)
            {
                // 是图片就加图片
                currentTree->child(i)->setIcon(0, QIcon(dirCurrent + strfileName));
            }
            else
            {
                // 是文件夹还要看是否已添加过item
                if (currentTree->child(i)->childCount() == 0)
                {
                    QString dirTemp = getDirFromItem(currentTree->child(i));
                    addFileItem(dirTemp, currentTree->child(i));
                }
                else if (currentTree->child(i)->childCount() > 0 &&
                         currentTree->child(i)->isExpanded())
                {
                    SetChildItemIconPic(currentTree->child(i));
                }
            }
        }        
        return;
    }
}

void DsResourceDisplay::unExpandSomething(QTreeWidgetItem *treeItem)
{
    setChildItemIconNull(treeItem);
}

QString DsResourceDisplay::getDirFromItem(QTreeWidgetItem *currentTreeItem)
{
    QString pathPre;
    QString pathTemp;
    if (currentTreeItem == NULL)
    {
        return pathPre + '/';
    }
    else
    {
        QTreeWidgetItem *treeWidgetItemTemp = currentTreeItem;
        for ( ; treeWidgetItemTemp != NULL; treeWidgetItemTemp = treeWidgetItemTemp->parent())
        {
            pathTemp = treeWidgetItemTemp->text(0);
            if (pathTemp.right(1) != QString('/'))
            {
                pathTemp += '/';
            }
            pathTemp += pathPre;
            pathPre = pathTemp;
        }
        return (m_dir + pathPre);
    }
}

QString DsResourceDisplay::getParentDirFromItem(QTreeWidgetItem *currentTreeItem)
{
    QString pathPre;
    QString pathTemp;
    if (currentTreeItem == NULL)
    {
        return pathPre + '/';
    }
    else
    {
        return getDirFromItem(currentTreeItem->parent());
    }
}

void DsResourceDisplay::contextMenuEvent(QContextMenuEvent *event)
{
    m_menu->popup(QCursor::pos());
}

// 为当前的 Item （其目录为strDir）创建子目录
int DsResourceDisplay::addFileItem(QString strDir, QTreeWidgetItem *currentItem)
{
    if (strDir.right(1) != QString('/'))
    {
        strDir += '/';
    }

    QDir dir(strDir);
    if (!dir.exists())
    {
        return -1;
    }
    dir.setFilter(QDir::Dirs | QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();

    int i = 0;
    do
    {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." ||
                fileInfo.fileName() == ".." ||
                fileInfo.fileName() == "...")
        {
            i++;
            continue;
        }
        bool bisDir = fileInfo.isDir();
        bool enableAddSign = false;
        if (bisDir)
        {
            enableAddSign = true;
        }
        else if (fileInfo.fileName().right(4).compare(".jpg", Qt::CaseInsensitive) == 0 ||
                 fileInfo.fileName().right(4).compare(".bmp", Qt::CaseInsensitive) == 0 ||
                 fileInfo.fileName().right(4).compare(".tag", Qt::CaseInsensitive) == 0 ||
                 fileInfo.fileName().right(4).compare(".png", Qt::CaseInsensitive) == 0)
        {
            enableAddSign = true;
        }
        if (enableAddSign)
        {
            QTreeWidgetItem *noteTemp = new QTreeWidgetItem();
            noteTemp->setText(0, fileInfo.fileName());
            currentItem->addChild(noteTemp);
            noteTemp->setIcon(0, QIcon(DS_FB_FILE_SMALL)); // 反正生成时看不见，用啥图标都可以，待到展开时有其他函数改图标
        }
        i++;
    }
    while (i < list.size());

    return 0;
}

void DsResourceDisplay::deleteItem(QTreeWidgetItem *currentTreeItem)
{
    if (currentTreeItem != NULL)
    {
        int childCount = currentTreeItem->childCount();
        QTreeWidgetItem *childItem = NULL;
        for (int i = 0; i < childCount; ++i)
        {
            childItem = currentTreeItem->child(0);
            if (childItem->childCount() > 0)
            {
                deleteItem(childItem);
            }
            else
            {
                delete childItem;
            }
            childItem = NULL;
        }
        delete currentTreeItem;
        currentTreeItem = NULL;
    }
}

void DsResourceDisplay::setChildItemIconNull(QTreeWidgetItem *currentItem)
{
    int childCount = currentItem->childCount();
    for (int i = 0; i < childCount; ++i)
    {
        if (currentItem->child(i)->childCount() > 0)
        {
            setChildItemIconNull(currentItem->child(i));
        }
        else
        {
            currentItem->child(i)->setIcon(0, QIcon(DS_FB_FILE_SMALL));
        }
    }
}

void DsResourceDisplay::SetChildItemIconPic(QTreeWidgetItem *currentItem)
{
    int nchildCount = currentItem->childCount();

    if (nchildCount > 0) // 貌似能展开都不会为0
    {
        QString strfileName;
        // 先遍历这个Item为路径是否有文件夹，若有则添加
        QString dirCurrent = getDirFromItem(currentItem);
        for (int i = 0; i < nchildCount; ++i)
        {
            strfileName = currentItem->child(i)->text(0);

            if (strfileName.right(4).compare(".jpg", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".bmp", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".tag", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".png", Qt::CaseInsensitive) == 0)
            {
                // 是图片就加图片
                currentItem->child(i)->setIcon(0, QIcon(dirCurrent + strfileName));
            }
            else
            {
                // 是文件夹还要看是否已添加过item
                if (currentItem->child(i)->childCount() > 0 &&
                        currentItem->child(i)->isExpanded())
                {
                    SetChildItemIconPic(currentItem->child(i));
                }
            }
        }
        return;
    }
}

void DsResourceDisplay::debugSomething()
{
    qDebug() << "Hello world";
    QMessageBox::information(this, "Document", "Hello World!", QMessageBox::Ok);
}

void DsResourceDisplay::refreshFolder()
{
    int ntreeCount = m_tree->columnCount();
    QTreeWidgetItem *currentItem = NULL;
    for (int i = 0; i < ntreeCount; ntreeCount--)
    {
        currentItem = m_tree->topLevelItem(i);
        m_tree->takeTopLevelItem(i);
        deleteItem(currentItem);
        currentItem = NULL;
    }

    m_dir = QString("");
    DsData *dsDataTemp = DsData::shareData();
    if (dsDataTemp == NULL)
    {
        return;
    }
    else
    {
        DsProject *dsProjectTemp = dsDataTemp->getProject();
        if (dsProjectTemp != NULL)
        {
            std::string strRes = dsProjectTemp->getDirName();
            char szdata[1024] = {'\0'};
            strncpy(szdata, strRes.data(), 1024); //--// string to char*
            m_dir = QString(szdata); // szdata末尾带了 /
            addResFolder(m_dir + QString("textures"), QString("textures"));
        }
    }
}
