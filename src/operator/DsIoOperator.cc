#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <assert.h>
#include "model/DsModel.h"
#include "model/DsData.h"
#include "DsIoOperator.h"
#include "DsOperator.h"
#include "util/DsUtil.h"
#include "util/DsDebug.h"

DsIoOperator::DsIoOperator()
{
	m_mainWidget=NULL;
	m_saveDialog=NULL;
	m_loadDialog=NULL;
	m_data=DsData::shareData();
}
void DsIoOperator::newProject()
{

    QString file=QFileDialog::getSaveFileName(
                m_mainWidget,
                QString("Open FSprite Project"),
                QString("."),
                QString("FSprite File(*.fproj)"));

    if(file.length()==0)
    {
        return;
    }
    QFileInfo file_info(file);


    file=file_info.absoluteFilePath();
    QString dir_name=file_info.path()+"/";
    QString file_name=file_info.fileName();



    DsProject* proj=new DsProject;
    proj->setDirName(dir_name.toStdString());
    proj->setFileName(file_name.toStdString());
    m_data->setProject(proj);
    m_data->emitSignal(DsData::SG_CUR_PROJECT_CHANGE);

}




void DsIoOperator::saveProject()
{
    DsProject*  proj=m_data->getProject();
    if(proj==NULL)
    {
        return;
    }
    QString fileName;
    fileName= proj->getFileName().c_str();
    QFile file(fileName);
    DsUtil::saveProject(proj);
}



void DsIoOperator::loadProject()
{
    DsProject* old_proj=m_data->getProject();
    if(old_proj)
    {
        QMessageBox::information(NULL,"Load Project","Project Change But Not Save",QMessageBox::Yes);
    }

    QString file=QFileDialog::getOpenFileName(
                m_mainWidget,
                QString("Open FSprite Project"),
                QString("."),
                QString("FSprite File(*.fproj)"));
    if(file.length()==0)
    {
        return;
    }
    QFileInfo file_info(file);
    file=file_info.absoluteFilePath();
    QString dir_name=file_info.path()+"/";
    QString file_name=file_info.fileName();
    std::string log_msg;
    DsProject* proj=DsUtil::loadProject(dir_name.toStdString(),file_name.toStdString(),log_msg);

    if(proj==NULL)
    {
        QMessageBox::information(NULL,"LoadProject",QString("Load Sprite Failed:")+log_msg.c_str(),QMessageBox::Yes);
        return;
    }
    m_data->setProject(proj);
    m_data->emitSignal(DsData::SG_CUR_PROJECT_CHANGE);
}












