#include <string.h>
#include <QLabel>
#include <QVBoxLayout>
#include "DsQrcMacros.h"
#include "DsResourceDisplay.h"
#include "src/model/DsData.h"
#include "src/model/DsProject.h"
#include <QFileIconProvider>

extern DsData* s_shareData;

DsResourceDisplay::DsResourceDisplay(QWidget* p)
    :QWidget(p)
{
    // 加一个右键菜单
    m_menu = new QMenu(this);
    m_flushAction = m_menu->addAction(tr("refresh"));
    connect(m_flushAction, SIGNAL(triggered()), this, SLOT(RefreshFolder()));

    m_model = new QDirModel;
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

    //QPushButton *flushButton = new QPushButton("flush", this);
    //connect(flushButton, SIGNAL(clicked()), this, SLOT(flushFolder()));

    //QHBoxLayout *downLayout = new QHBoxLayout;
    //downLayout->addWidget(flushButton, 0, Qt::AlignHCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout, 0);
    //mainLayout->addLayout(downLayout, 1);
    setLayout(mainLayout);

    connect(DsData::shareData(), SIGNAL(signalCurProjectChange()), this, SLOT(RefreshFolder()));
}

void DsResourceDisplay::AddResFolder(QString strPath, QString itemName)
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
        AddFileItem(strPath, noteTemp);
    }
}

/*
void DsResourceDisplay::addResFolder(const std::string &folder)
{
    char szdata[1024] = {'\0'};
    strncpy(szdata,  folder.data(),1024); //--// string to char*
    QString strpath(szdata);
    if (!strpath.isNull()) // user choiced folder
    {
        if (strpath.right(1) != QString('/'))
        {
            strpath += '/';
        }
        QTreeWidgetItem *noteTemp = new QTreeWidgetItem();
        noteTemp->setText(0, strpath);
        noteTemp->setIcon(0, QIcon(DS_FB_FILE)); // 待改进
        m_tree->addTopLevelItem(noteTemp);
        AddFileItem(strpath, noteTemp);
    }
}
*/

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
            dirTemp = GetParentDirFromItem(m_tree->currentItem());

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
        QString dirCurrent = GetDirFromItem(currentTree);
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
                    QString dirTemp = GetDirFromItem(currentTree->child(i));
                    AddFileItem(dirTemp, currentTree->child(i));
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
    SetChildItemIconNull(treeItem);
}

/*
void DsResourceDisplay::openSomething() // add一个文件夹
{
    QString filename = QFileDialog::getExistingDirectory(this, "Open Dir", m_dir, QFileDialog::ShowDirsOnly);
    if (!filename.isNull()) // user choiced folder
    {
        m_dir = filename;
        if (m_dir.right(1) != QString('/'))
        {
            m_dir += '/';
        }
        QTreeWidgetItem *noteTemp = new QTreeWidgetItem();
        noteTemp->setText(0, m_dir);
        noteTemp->setIcon(0, QIcon(DS_FB_FILE));
        m_tree->addTopLevelItem(noteTemp);
        AddFileItem(m_dir, noteTemp);

        std::string path(qPrintable(m_dir));

        emit resFolderAdd(path);
    }
}
*/

/*
void DsResourceDisplay::deleteSomething()
{
    if (m_tree->currentItem() != NULL)
    {
        QTreeWidgetItem *currentItem = m_tree->currentItem();
        if (currentItem->parent() == NULL)
        {
            QString dirTemp;
            dirTemp = GetDirFromItem(currentItem); // 获得路径

            // 删除一系列节点
            int nitemIndex = m_tree->indexOfTopLevelItem(currentItem);
            m_tree->takeTopLevelItem(nitemIndex);
            DeleteItem(currentItem);
            currentItem = NULL;

            std::string path(qPrintable(dirTemp));
            emit resFolderDelete(path);
        }
    }
}
*/

QString DsResourceDisplay::GetDirFromItem(QTreeWidgetItem *currentTreeItem)
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

QString DsResourceDisplay::GetParentDirFromItem(QTreeWidgetItem *currentTreeItem)
{
    QString pathPre;
    QString pathTemp;
    if (currentTreeItem == NULL)
    {
        return pathPre + '/';
    }
    else
    {
        return GetDirFromItem(currentTreeItem->parent());
    }
}

void DsResourceDisplay::contextMenuEvent(QContextMenuEvent *event)
{
    m_menu->popup(QCursor::pos());
}

// 为当前的 Item （其目录为strDir）创建子目录
int DsResourceDisplay::AddFileItem(QString strDir, QTreeWidgetItem *currentItem)
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
            noteTemp->setIcon(0, QIcon(DS_FB_FILE)); // 反正生成时看不见，用啥图标都可以，待到展开时有其他函数改图标
        }
        i++;
    }
    while (i < list.size());

    return 0;
}

void DsResourceDisplay::DeleteItem(QTreeWidgetItem *currentTreeItem)
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
                DeleteItem(childItem);
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

void DsResourceDisplay::SetChildItemIconNull(QTreeWidgetItem *currentItem)
{
    int childCount = currentItem->childCount();
    for (int i = 0; i < childCount; ++i)
    {
        if (currentItem->child(i)->childCount() > 0)
        {
            SetChildItemIconNull(currentItem->child(i));
        }
        else
        {
            currentItem->child(i)->setIcon(0, QIcon(DS_FB_FILE));
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
        QString dirCurrent = GetDirFromItem(currentItem);
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

/*
void DsResourceDisplay::DeleteChildItem(QTreeWidgetItem *currentTreeItem)
{
    if (currentTreeItem != NULL)
    {
        int childCount = currentTreeItem->childCount();
        QTreeWidgetItem *childItem = NULL;
        for (int i = 0; i < childCount; ++i)
        {
            childCount = currentTreeItem->child(0);
            if (childItem->childCount() > 0)
            {
                DeleteItem(childItem);
            }
            else
            {
                delete childItem;
            }
            childItem = NULL;
        }
    }
}
*/

void DsResourceDisplay::debugSomething()
{
    qDebug() << "Hello world";
    QMessageBox::information(this, "Document", "Hello World!", QMessageBox::Ok);
}

/*
void DsResourceDisplay::AddResFolder()
{
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
            strRes += "textures";
            char szdata[1024] = {'\0'};
            strcpy_s(szdata, 1024, strRes.data()); //--// string to char*
            AddResFolder(szdata);
        }
    }
}
*/

void DsResourceDisplay::RefreshFolder()
{
    int ntreeCount = m_tree->columnCount();
    QTreeWidgetItem *currentItem = NULL;
    for (int i = 0; i < ntreeCount; ntreeCount--)
    {
        currentItem = m_tree->topLevelItem(i);
        m_tree->takeTopLevelItem(i);
        DeleteItem(currentItem);
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
            strcpy_s(szdata, 1024, strRes.data()); //--// string to char*
            m_dir = QString(szdata); // szdata末尾带了 /
            AddResFolder(m_dir + QString("textures"), QString("textures"));
        }
    }

    //QMessageBox::information(this, "Document", "Hello World!", QMessageBox::Ok);
    //QMessageBox::information(this, "Document", "444444444", QMessageBox::Ok);
    //m_tree->takeTopLevelItem(0);
    /*
    QTreeWidgetItem *treeWidgetItemTemp = m_tree->headerItem();

    if (treeWidgetItemTemp != NULL)
    {
        DeleteItem(treeWidgetItemTemp);
        treeWidgetItemTemp = NULL;
    }
    */

    //QTreeWidgetItem *currentItem = m_tree->headerItem();
    /*
    QTreeWidgetItem *currentItem = m_tree->currentItem();
    if (currentItem != NULL)
    {
        {
        int nitemIndex = m_tree->indexOfTopLevelItem(currentItem);
        QMessageBox::information(this, "Document", QString::number(nitemIndex), QMessageBox::Ok);
        }

        {
        int nitemIndex = m_tree->indexOfTopLevelItem(m_tree->headerItem());
        QMessageBox::information(this, "Document", QString::number(nitemIndex), QMessageBox::Ok);
        }
        */

        /*
        if (m_tree->currentItem() == currentItem)
        {
               QMessageBox::information(this, "Document", "444444444", QMessageBox::Ok);
        }
        delete currentItem;
        currentItem = NULL;
        */
        /*
        if (currentItem->parent() == NULL)
        {
            // 删除一系列节点
            int nitemIndex = m_tree->indexOfTopLevelItem(currentItem);
            m_tree->takeTopLevelItem(nitemIndex);
            DeleteItem(currentItem);
            currentItem = NULL;
        }
        */
        /*
    }

    addResFolder();
    */
}
