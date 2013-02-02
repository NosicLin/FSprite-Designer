#include <QLabel>
#include <QVBoxLayout>
#include "DsQrcMacros.h"
#include "DsResourceDisplay.h"

DsResourceDisplay::DsResourceDisplay(QWidget* p)
	:QWidget(p)
{
    /* TODO(use real tree widget here */
    //QLabel* tree= new QLabel(tr("Tree Control List\n  Folder1\n    File1.jpg\n    File2.png\n  Folder2\n    File1.bmp\n    File2.tga\n"), this);

    /* TODO(use your control here)*/
    //QLabel* controlbar= new QLabel(tr("<add> <delete>"), this);

    //QLabel* controlbar= new QLabel(tr(" ----------------\n|<add>| <delete> |\n ----------------"),this);

    /*
    QVBoxLayout* hbox=new QVBoxLayout(this);

    hbox->addWidget(tree, 1, Qt::AlignTop);
    hbox->addWidget(controlbar,0);

    setLayout(hbox);
    */

    /*
    std::string strTemp("aaa");
    char szdata[1024] = {'\0'};
    strcpy_s(szdata, 1024, strTemp.data());
    QMessageBox::information(this, "Document", QString(szdata), QMessageBox::Ok);
    */


    m_dir = QString("E:/"); // default setting. undetermined
    m_tree = new QTreeWidget;
    m_tree->setColumnCount(1);
    m_tree->setHeaderLabel("Path");
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
        noteTemp->setIcon(0, QIcon(DS_FB_FILE));
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

        if(CmpTypeByWM(szdata, "jpg") == 0 ||
                CmpTypeByWM(szdata, "bmp") == 0 ||
                //CmpTypeByWM(szfileName, "gif") == 0 ||
                CmpTypeByWM(szdata, "tag") == 0 ||
                CmpTypeByWM(szdata, "png") == 0)
        {
            dirTemp = GetParentDirFromItem(m_tree->currentItem());
            byteTemp = dirTemp.toLocal8Bit();
            strcpy_s(szdata, 1024, byteTemp.data());
            std::string path(szdata); //--// char* to string
            emit resFileSelect(path, filename);
            //QMessageBox::information(this, "test", dirTemp + fileName, QMessageBox::Ok);
        }
    }
}

void DsResourceDisplay::expandSomething(QTreeWidgetItem *treeItem)
{
    QTreeWidgetItem *currentTree = treeItem;
    int nchildCount = currentTree->childCount();

    if (nchildCount != 0) // 貌似能展开都不会为0
    {
        char szfileName[1024] = {'\0'};
        QByteArray byteTemp;
        QString strfileName;
        // 先遍历这个Item为路径是否有文件夹，若有则添加
        for(int i = 0; i < nchildCount; ++i)
        {
            strfileName = currentTree->child(i)->text(0);
            QByteArray byteTemp = strfileName.toLocal8Bit();
            strcpy_s(szfileName, 1024, byteTemp.data());

            if(CmpTypeByWM(szfileName, "jpg") == 0 ||
                    CmpTypeByWM(szfileName, "bmp") == 0 ||
                    //CmpTypeByWM(szfileName, "gif") == 0 ||
                    CmpTypeByWM(szfileName, "tag") == 0 ||
                    CmpTypeByWM(szfileName, "png") == 0)
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
                    //QMessageBox::information(this, "Document", dirTemp, QMessageBox::Ok);
                }
            }
        }
        //m_tree->expandItem(currentTree);
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
            int nitemIndex = m_tree->indexOfTopLevelItem(currentItem);
            currentItem->takeChildren();
            m_tree->takeTopLevelItem(nitemIndex);

            QByteArray byteTemp;
            char szdata[1024] = {'\0'};

            byteTemp = dirTemp.toLocal8Bit();
            strcpy_s(szdata, 1024, byteTemp.data()); //--// QString to char*
            std::string path(szdata);

            emit resFolderDelete(path);
        }
    }
}

void DsResourceDisplay::debugSomething()
{
    /* // example
        //QString fileNameTemp = GetDirFromItem(m_tree->currentItem());
        //QString fileName = fileNameTemp.left(fileNameTemp.length() - 1);
    QString str = "Hello world";
    QChar *data = str.data();
    while (!data->isNull()) {
        qDebug() << data->unicode();
        ++data;
    }
    QTreeWidgetItem *note1 = new QTreeWidgetItem(QStringList("note1"));
    tree->addTopLevelItem(note1);

    QTreeWidgetItem *note2 = new QTreeWidgetItem(QStringList("note2"));
    tree->addTopLevelItem(note2);

    tree->expand(tree->model()->index(1, 0));

    QTreeWidgetItem *note3 = new QTreeWidgetItem(QStringList("note3"));
    tree->addTopLevelItem(note3);

    QTreeWidgetItem *childtree1 = new QTreeWidgetItem(QStringList("child1"));
    QTreeWidgetItem *childtree2 = new QTreeWidgetItem(QStringList("child2"));
    note2->addChild(childtree1);
    note2->addChild(childtree2);
    */
    qDebug() << "Hello world";
    QMessageBox::information(this, "Document", "Hello World!", QMessageBox::Ok);
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
    char dir[1024] = {'\0'};
    char fileDir[1024] = {'\0'};
    //QByteArray byteTemp = strDir.toLatin1();
    if (strDir.right(1) != QString('/'))
    {
        strDir += '/';
    }
    QByteArray byteTemp = strDir.toLocal8Bit();
    _finddata_t ffile;
    int ndone = -1;
    int nret = 0;

    strcpy_s(dir, 1024, byteTemp.data());
    strcat_s(fileDir, 1024, dir);
    strcat_s(fileDir, 1024, "*.*");

    ndone = _findfirst(fileDir, &ffile);
    nret = 0;
    if(ndone != -1)
    {
        for( ; nret != -1; )
        {
            if(strcmp(ffile.name, ".") != 0 &&
                    strcmp(ffile.name, "..") != 0 &&
                    strcmp(ffile.name, "...") != 0)
            {
                if (ffile.attrib == _A_SUBDIR ||
                        CmpTypeByWM(ffile.name, "jpg") == 0 ||
                        CmpTypeByWM(ffile.name, "bmp") == 0 ||
                        //CmpTypeByWM(ffile.name, "gif") == 0 ||
                        CmpTypeByWM(ffile.name, "tag") == 0 ||
                        CmpTypeByWM(ffile.name, "png") == 0)
                {
                    QTreeWidgetItem *noteTemp = new QTreeWidgetItem();
                    //noteTemp->setText(0, ffile.name);
                    //--// char* to QString
                    noteTemp->setText(0, QTextCodec::codecForName("GBK")->toUnicode(ffile.name));
                    currentItem->addChild(noteTemp);

                    if (ffile.attrib == _A_SUBDIR)
                    {
                        noteTemp->setIcon(0, QIcon(DS_FB_FILE));
                    }
                    else
                    {
                        //添加图片图标
                        QString fileNameTemp = GetDirFromItem(noteTemp);
                        QString fileName = fileNameTemp.left(fileNameTemp.length() - 1);
                        noteTemp->setIcon(0, QIcon(fileName));
                    }
                }
            }
            nret = _findnext(ndone, &ffile);
        }
    }

    return 0;
}

int DsResourceDisplay::StrCmpByWM(const char *szstrT, const char *szstrS)
{
    if(szstrT == NULL && szstrS == NULL)
    {
        return 0;
    }
    else if(szstrT == NULL && szstrS != NULL)
    {
        return szstrS[0];
    }
    else if(szstrT != NULL && szstrS == NULL)
    {
        return -1 * szstrT[0];
    }
    else
    {
        int i = 0;
        int num = 0;
        char chstrT;
        char chstrS;
        for ( ; (*(szstrT + i) != '\0') && (*(szstrS + i) != '\0'); ++i)
        {
            if(*(szstrT + i) >= 'A' && *(szstrT + i) <= 'Z')
            {
                chstrT = *(szstrT + i) + 32;
            }
            else
            {
                chstrT = *(szstrT + i);
            }

            if(*(szstrS + i) >= 'A' && *(szstrS + i) <= 'Z')
            {
                chstrS = *(szstrS + i) + 32;
            }
            else
            {
                chstrS = *(szstrS + i);
            }

            num = chstrS - chstrT;
            if (num != 0)
            {
                return num;
            }
        }

        if(*(szstrT + i) >= 'A' && *(szstrT + i) <= 'Z')
        {
            chstrT = *(szstrT + i) + 32;
        }
        else
        {
            chstrT = *(szstrT + i);
        }

        if(*(szstrS + i) >= 'A' && *(szstrS + i) <= 'Z')
        {
            chstrS = *(szstrS + i) + 32;
        }
        else
        {
            chstrS = *(szstrS + i);
        }
        num = chstrS - chstrT;
        return num;
    }
}

int DsResourceDisplay::CmpTypeByWM(const char *filename, const char *type)
{
    int len = strlen(filename);
    int i = 0;
    for(i = len - 1; i >= 0; --i)
    {
        if(*(filename + i) == '.')
        {
            if(0 == StrCmpByWM(filename + i + 1, type))
            {
                return 0;
            }
            return 1;
        }
    }
    return 1;
}
