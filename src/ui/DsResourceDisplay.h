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

class DsResourceDisplay:public QWidget
{
	Q_OBJECT
	public:
        DsResourceDisplay(QWidget* p);
    public:
        void addResFolder(const std::string& folder);
        void addAcceptFileType(const std::string& ext); // 预留

    signals:
        void resFolderDelete(const std::string& folder);
        void resFolderAdd(const std::string& floader);
        void resFileSelect(const std::string& path, const std::string& name);

    //-----------------------------------//
    private:
        QDirModel *m_model;
        QTreeWidget *m_tree;
        QString m_dir;
        QString GetDirFromItem(QTreeWidgetItem *currentTreeItem);
        QString GetParentDirFromItem(QTreeWidgetItem *currentTreeItem);

        int AddFileItem(QString strDir, QTreeWidgetItem *currentItem); // strDir的末尾最好有'/'
        void DeleteItem(QTreeWidgetItem *currentTreeItem); // 删除一些列节点

    private slots:
        void selectSomething(void);
        void expandSomething(QTreeWidgetItem *treeItem);
        void openSomething(void);
        void deleteSomething(void);
        void debugSomething(void);
        void addResFolder();
};


#endif 




