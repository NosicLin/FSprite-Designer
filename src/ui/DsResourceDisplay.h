#ifndef _DS_RESOURCE_DISPLAY_H_
#define _DS_RESOURCE_DISPLAY_H_
#include <QWidget>
#include <string>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QDir>
#include <QVBoxLayout>

class DsResourceDisplay:public QWidget
{
	Q_OBJECT
	public:
        DsResourceDisplay(QWidget* p);

    signals:
        void resFileSelect(const std::string& path, const std::string& name);

    //-----------------------------------//
    private:
        QTreeWidget *m_tree;
        QMenu *m_menu;
        QAction *m_flushAction;
        QString m_dir; // 用于保存根目录

        QString getDirFromItem(QTreeWidgetItem *currentTreeItem);
        QString getParentDirFromItem(QTreeWidgetItem *currentTreeItem);

        void addResFolder(QString strPath, QString itemName); // 添加一个根目录
        int addFileItem(QString strDir, QTreeWidgetItem *currentItem); // strDir的末尾最好有'/' // 添加一个子目录 // 为当前的 Item （其目录为strDir）创建子目录

        void contextMenuEvent(QContextMenuEvent *event); // 鼠标右键弹出时的事件响应

        void deleteItem(QTreeWidgetItem *currentTreeItem); // 删除一系列节点，包括本节点
        void setChildItemIconNull(QTreeWidgetItem *currentItem); // 设置该节点的子节点的图标为小图标
        void SetChildItemIconPic(QTreeWidgetItem *currentItem); // 设置节点的子节点的图标为图片 （不添加和删除节点）

    private slots:
        void selectSomething(void); // 选择一个图标，返回路径和文件名
        void expandSomething(QTreeWidgetItem *treeItem); // 展开一个Item
        void unExpandSomething(QTreeWidgetItem *treeItem); // 收缩一个Item
        void debugSomething(void); //
        void refreshFolder(); //
};


#endif 




