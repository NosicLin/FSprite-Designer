#include <QMessageBox>
#include <QFileDialog>
#include <assert.h>
#include "model/DsModel.h"
#include "model/DsData.h"
#include "DsIoOperator.h"
#include "DsOperator.h"
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
    DsProject*  proj=m_data->getProject(name);
    assert(proj);

    QString fileName;
    fileName= proj->getFileName().c_str();

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Truncate))
    {
        QMessageBox::information(NULL,"Save Sprite","Open File Failed");
        return;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    DsSpriteUtil::saveProject(proj,writer);
    proj->setFileName(fileName.toStdString());
}

void DsIoOperator::loadProject()
{
    QString file=QFileDialog::getOpenFileName(
                m_mainWidget,
                QString("Open FSprite Project"),
                QString("."),
                QString("FSprite File(*.fproj)"));

    if(file.length()==0)
    {
        return;
    }

    std::string msg("failed");
    DsProject* proj=DsSpriteUtil::loadProject(file.toStdString());
    if(proj==NULL)
    {
        QMessageBox::information(NULL,QString("Load Sprite Failed"));
        return;
    }

    proj->setFileName(file.toStdString());
    m_data->setCurProject(proj);
    m_data->emitSignal(DsData::SG_CUR_PROJECT_CHANGE);
}

void DsIoOperator::saveProject()
{
    DsProject* project=DsData::shareData()->getCurProject();
    if(project!=NULL)
    {
        saveProject(project->getName());
    }
}


