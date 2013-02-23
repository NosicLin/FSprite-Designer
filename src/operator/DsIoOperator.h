#ifndef _DS_IO_OPERATOR_H_
#define _DS_IO_OPERATOR_H_

#include <string>
class DsIoOperator 
{
	public:
		DsIoOperator();
    public:
        void newProject();
        void saveProject();
        void loadProject();
        void exportFSprite(const std::string& id);

	private:
		QWidget* m_mainWidget;
		QDialog* m_saveDialog;
		QDialog* m_loadDialog;
		DsData* m_data;
};

#endif /*_DS_IO_OPERATOR_H_*/




