#include <QMessageBox>
#include <QFileDialog>
#include <assert.h>
#include "model/DsModel.h"
#include "model/DsData.h"
#include "DsIoOperator.h"
#include "util/DsSpriteUtil.h"

DsIoOperator::DsIoOperator()
{
	m_mainWidget=NULL;
	m_saveDialog=NULL;
	m_loadDialog=NULL;
	m_data=DsData::shareData();
}


void DsIoOperator::saveProject(const std::string& name)
{
    /*
	DsProject*  proj=m_data->getProject(name);
	assert(proj);
	QString file=QFileDialog::getSaveFileName(
			m_mainWidget,
			QString("Save FSprite"),
			QString(proj->getFilePath().c_str()),
			tr("FSprite File(*.xml"));
	
	if(file.length()==0)
	{
		QMessageBox::information(NULL,tr("Path"),tr("You didn't select any files"));
	}
	else 
	{
		std::string msg=SpriteUtil::save(proj,std::string(file.toLatin1.data()));
		if(msg.size()!=0)
		{
			QMessageBox::information(NULL,tr("path"),QString(msg.c_str()));
		}
    }
    */
}

void DsIoOperator::loadProject()
{
    QString file=QFileDialog::getOpenFileName(
            m_mainWidget,
            QString("Open FSprite"),
            QString("."),
            QString("FSprite File(*.xml)"));

    if(file.length()==0)
    {
        return;
    }

    std::string msg;
    DsProject* proj=DsSpriteUtil::loadProject(file.toStdString(),msg);
    if(proj==NULL)
    {
        QMessageBox::information(NULL,QString("Load Sprite"),QString(msg.c_str()));
        return;
    }
    m_data->addProject(proj);
    m_data->setCurProject(proj->getName());
    m_data->emitSignal(DsData::SG_DATA_PROPERTY_CHANGE);
}


