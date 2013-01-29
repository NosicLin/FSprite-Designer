#ifndef _DS_RESOURCE_DISPLAY_H_
#define _DS_RESOURCE_DISPLAY_H_
#include <QWidget>
#include <string>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <io.h>
#include <QDebug>
#include <QTextCodec>

class DsResourceDisplay:public QWidget 
{
	Q_OBJECT
	public:
        DsResourceDisplay(QWidget* p);
    public:
        void addResFolder(const std::string& folder);
        void addAcceptFileType(const std::string& ext);

    signals:
        void resFolderDelete(const std::string& folder);
        void resFolderAdd(const std::string& floader);
        void resFileSelect(const std::string& path, const std::string& name);

    private:
        QTreeWidget *m_tree;
        QString m_dir; // 用于保存上次打开的路径
        QString GetDirFromItem(QTreeWidgetItem *currentTreeItem); // 返回的路径末尾固定有'/'
        QString GetParentDirFromItem(QTreeWidgetItem *currentTreeItem);
        int AddFileItem(QString strDir, QTreeWidgetItem *currentItem); // strDir的末尾最好有'/'
        int StrCmpByWM(const char *szstrT, const char *szstrS);
        int CmpTypeByWM(const char *filename,const char *type);

    private slots:
        void addSomething(void);
        void expandSomething(QTreeWidgetItem *treeItem);
        void openSomething(void);
        void deleteSomething(void);
        void debugSomething(void);
};


#endif 




