#ifndef _DS_RESOURCE_DISPLAY_H_
#define _DS_RESOURCE_DISPLAY_H_
#include <QWidget>
#include <string>
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
        void resFileSelect(const std::string& name);
};


#endif 




