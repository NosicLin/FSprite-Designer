#ifndef _DS_RESOURCE_DISPLAY_H_
#define _DS_RESOURCE_DISPLAY_H_
#include <QWidget>
#include <string>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTextCodec>
#include <QDirModel>
#include <QModelIndex>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QAction>
#include <QMenu>

class DsResourceDisplay:public QWidget
{
	Q_OBJECT
	public:
        DsResourceDisplay(QWidget* p);

        //void addResFolder(const std::string& folder);
        //void addAcceptFileType(const std::string& ext); // 预留

    signals:
        void resFileSelect(const std::string& path, const std::string& name);
        //void resFolderDelete(const std::string& folder);
        //void resFolderAdd(const std::string& floader);

    //-----------------------------------//
    private:
        QDirModel *m_model;
        QTreeWidget *m_tree;
        QMenu *m_menu;
        QAction *m_flushAction;
        QString m_dir; // 用于保存根目录

        QString GetDirFromItem(QTreeWidgetItem *currentTreeItem);
        QString GetParentDirFromItem(QTreeWidgetItem *currentTreeItem);

        void AddResFolder(QString strPath, QString itemName); // 添加一个根目录
        int AddFileItem(QString strDir, QTreeWidgetItem *currentItem); // strDir的末尾最好有'/' // 添加一个子目录 // 为当前的 Item （其目录为strDir）创建子目录

        void contextMenuEvent(QContextMenuEvent *event); // 鼠标右键弹出时的事件响应

        void DeleteItem(QTreeWidgetItem *currentTreeItem); // 删除一系列节点，包括本节点
        void SetChildItemIconNull(QTreeWidgetItem *currentItem); // 设置该节点的子节点的图标为小图标
        void SetChildItemIconPic(QTreeWidgetItem *currentItem); // 设置节点的子节点的图标为图片 （不添加和删除节点）

        //void DeleteChildItem(QTreeWidgetItem *currentTreeItem);
        //void AddResFolder(); // 根据当前目录添加文件夹

    private slots:
        void selectSomething(void); // 选择一个图标，返回路径和文件名
        void expandSomething(QTreeWidgetItem *treeItem); // 展开一个Item
        void unExpandSomething(QTreeWidgetItem *treeItem); // 收缩一个Item
        void debugSomething(void); //
        void RefreshFolder(); //

        //void openSomething(void); //
        //void deleteSomething(void); //
};


#endif 




