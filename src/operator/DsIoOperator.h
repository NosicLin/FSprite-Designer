#ifndef _DS_IO_OPERATOR_H_
#define _DS_IO_OPERATOR_H_

#include <string>
class DsIoOperator 
{
	public:
		DsIoOperator();
	public:
        void saveProject();
        void loadProject();
        void exportFSpriteByID(const std::string& id);

	private:
		QWidget* m_mainWidget;
		QDialog* m_saveDialog;
		QDialog* m_loadDialog;
		DsData* m_data;
};

#endif /*_DS_IO_OPERATOR_H_*/




