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
        QString m_dir;
        QString GetDirFromItem(QTreeWidgetItem *currentTreeItem);
        QString GetParentDirFromItem(QTreeWidgetItem *currentTreeItem);
        int AddFileItem(QString strDir, QTreeWidgetItem *currentItem);
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




