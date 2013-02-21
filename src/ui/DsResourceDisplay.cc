#include <QLabel>
#include <QVBoxLayout>
#include "DsQrcMacros.h"
#include "DsResourceDisplay.h"

DsResourceDisplay::DsResourceDisplay(QWidget* p)
	:QWidget(p)
{
    m_model = new QDirModel;
    m_dir = QString("E:/"); // default setting. undetermined
    m_tree = new QTreeWidget;
    m_tree->setColumnCount(1);
    m_tree->setHeaderLabel("Path");
    m_tree->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    connect(m_tree, SIGNAL(clicked(const QModelIndex &)), this, SLOT(addSomething()));
    connect(m_tree, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(expandSomething(QTreeWidgetItem *)));

    QPushButton *addButton = new QPushButton("add", this);
    connect(addButton, SIGNAL(clicked()), this, SLOT(openSomething()));

    QPushButton *deleteButton = new QPushButton("delete", this);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteSomething()));

    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addWidget(m_tree);
    QVBoxLayout *downLeftLayout = new QVBoxLayout;
    downLeftLayout->addWidget(addButton, 0, Qt::AlignHCenter);
    QVBoxLayout *downRightLayout = new QVBoxLayout;
    downRightLayout->addWidget(deleteButton, 0, Qt::AlignHCenter);
    QHBoxLayout *downLayout = new QHBoxLayout;
    downLayout->addLayout(downLeftLayout, 0);
    downLayout->addLayout(downRightLayout, 1);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout, 0);
    mainLayout->addLayout(downLayout, 1);
    setLayout(mainLayout);
}

void DsResourceDisplay::addResFolder(const std::string &folder)
{
    char szdata[1024] = {'\0'};
    strcpy_s(szdata, 1024, folder.data()); //--// string to char*
    QString strpath;
    strpath = QTextCodec::codecForName("GBK")->toUnicode(szdata);
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

void DsResourceDisplay::addSomething() // 点击图片图标，返回路径和文件名
{
    int num = m_tree->currentItem()->childCount();
    if (num == 0)
    {
        QString dirTemp;
        QString fileName;
        QByteArray byteTemp;
        char szdata[1024] = {'\0'};

        fileName = m_tree->currentItem()->text(0);
        byteTemp = fileName.toLocal8Bit();
        strcpy_s(szdata, 1024, byteTemp.data());
        std::string filename(szdata);

        if(fileName.right(4).compare(".jpg", Qt::CaseInsensitive) == 0 ||
                fileName.right(4).compare(".bmp", Qt::CaseInsensitive) == 0 ||
                fileName.right(4).compare(".tag", Qt::CaseInsensitive) == 0 ||
                fileName.right(4).compare(".png", Qt::CaseInsensitive) == 0)
        {
            dirTemp = GetParentDirFromItem(m_tree->currentItem());
            byteTemp = dirTemp.toLocal8Bit();
            strcpy_s(szdata, 1024, byteTemp.data());
            std::string path(szdata); //--// char* to string
            emit resFileSelect(path, filename);
        }
    }
}

void DsResourceDisplay::expandSomething(QTreeWidgetItem *treeItem)
{
    QTreeWidgetItem *currentTree = treeItem;
    int nchildCount = currentTree->childCount();

    if (nchildCount != 0) // 貌似能展开都不会为0
    {
        QString strfileName;
        // 先遍历这个Item为路径是否有文件夹，若有则添加
        for (int i = 0; i < nchildCount; ++i)
        {
            strfileName = currentTree->child(i)->text(0);

            if (strfileName.right(4).compare(".jpg", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".bmp", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".tag", Qt::CaseInsensitive) == 0 ||
                    strfileName.right(4).compare(".png", Qt::CaseInsensitive) == 0)
            {
                // 是图片就不管
            }
            else
            {
                // 是文件夹还要看是否已添加过item
                if (currentTree->child(i)->childCount() == 0)
                {
                    QString dirTemp = GetDirFromItem(currentTree->child(i));
                    AddFileItem(dirTemp, currentTree->child(i));
                }
            }
        }        
        return;
    }
}

void DsResourceDisplay::openSomething()
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

        QByteArray byteTemp;
        char szdata[1024] = {'\0'};

        byteTemp = m_dir.toLocal8Bit();
        strcpy_s(szdata, 1024, byteTemp.data());
        std::string path(szdata);

        emit resFolderAdd(path);
    }
}

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

            QByteArray byteTemp;
            char szdata[1024] = {'\0'};
            byteTemp = dirTemp.toLocal8Bit();
            strcpy_s(szdata, 1024, byteTemp.data()); //--// QString to char*
            std::string path(szdata);

            emit resFolderDelete(path);
        }
    }
}

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
        return pathPre;
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
        bool isDirSign = false;
        if (bisDir)
        {
            enableAddSign = true;
            isDirSign = true;
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
            //--// char* to QString
            noteTemp->setText(0, fileInfo.fileName());
            currentItem->addChild(noteTemp);
            if (isDirSign)
            {
                noteTemp->setIcon(0, QIcon(DS_FB_FILE)); // 待改进
            }
            else
            {
                //添加图片图标
                QString fileNameTemp = GetDirFromItem(noteTemp);
                QString fileName = fileNameTemp.left(fileNameTemp.length() - 1);
                noteTemp->setIcon(0, QIcon(DS_TL_NEW)); // 待改进
            }
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

void DsResourceDisplay::debugSomething()
{
    qDebug() << "Hello world";
    QMessageBox::information(this, "Document", "Hello World!", QMessageBox::Ok);
}
