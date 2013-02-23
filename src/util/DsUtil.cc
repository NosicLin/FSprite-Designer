#include <time.h>
#include <QFile>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QUuid>
#include <QDir>

#include "DsUtil.h"
#include "util/DsUtilLoader.h"
#include "util/DsDebug.h"


QString DsUtil::stoq(const std::string str)
{
	return QString(str.c_str());
}

std::string DsUtil::qtos(const QString& q)
{
    return std::string(q.toLatin1().data());
}


std::string DsUtil::uniqueStringID()
{
    return QUuid::createUuid().toString().toStdString();
}

std::string DsUtil::integerToHexStr(long value)
{
	char buf[9];
	buf[8]=0;
	for(int i=0;i<8;i++)
	{
		int v= (0xf)&(value>>i*4);
		if(v<=9)
		{
			buf[i]=v+'0';
		}
		else
		{
			buf[i]=v-10+'a';
		}
	}
	return std::string(buf);
}

bool DsUtil::makeDirExist(const std::string& dir_name)
{
    QDir dir;
    return dir.mkpath(dir_name.c_str());
}
DsProject* DsUtil::loadProject(const std::string& dir_name,const std::string& file_name,std::string& msg)
{
    DsProjectLoader loader(dir_name,file_name);
    DsProject* proj=loader.loadProject();
    if(proj==NULL)
    {
        msg=loader.getLogMsg();
    }
    return proj;
}

bool DsUtil::saveProject(DsProject* proj)
{
	std::string dir_name=proj->getDirName();
    saveProjectFile(proj);
	for(int i=0;i<proj->getSpriteNu();i++)
	{
        DsSprite* sprite=proj->getSprite(i);
        std::string spriteName=sprite->getName()+"-"+sprite->getID();
        saveSpriteFile(dir_name,spriteName,sprite);
	}
    return true;
}


bool DsUtil::saveProjectFile(DsProject* proj)
{
	std::string dir_name=proj->getDirName();
    std::string file_name=proj->getFileName();

    DsDebug<<"dir_name:"<<dir_name.c_str()<<endl;
    DsDebug<<"file_name"<<file_name.c_str()<<endl;

    std::string file_path=dir_name+file_name;

	DsUtil::makeDirExist(dir_name);

    QFile file(file_path.c_str());
    if(!file.open(QFile::WriteOnly|QFile::Text))
	{
        QMessageBox::information(NULL,"SaveProject",QString("Open File:(")+file_path.c_str()+")Failed",QMessageBox::Yes);
        return false;
	}
	QXmlStreamWriter writer(&file);

	writer.setAutoFormatting(true);
	
	writer.writeStartDocument();
	writer.writeStartElement("FSpriteDesigner");
	writer.writeAttribute("version","v1.0");
    writer.writeAttribute("type","FSpriteProject");
	writer.writeStartElement("Sprites");

	for(int i=0;i<proj->getSpriteNu();i++)
	{
		DsSprite* sprite=proj->getSprite(i);
		std::string spriteName=std::string("sprites/")+sprite->getName()+"-"+sprite->getID();
		writer.writeStartElement("Sprite");
        writer.writeTextElement("url",spriteName.c_str());
		writer.writeEndElement();
	}
	writer.writeEndElement();
    writer.writeEndElement();
    return true;
}

bool DsUtil::saveSpriteFile(const std::string& dir_name,const std::string& file_name,DsSprite* sprite)
{
    DsUtil::makeDirExist(dir_name+"sprites");
    std::string file_path=dir_name+"sprites/"+file_name;
    QFile file(file_path.c_str());
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::information(NULL,"SaveProject",QString("Open File:(")+file_path.c_str()+")Failed",QMessageBox::Yes);
        return false;
    }
    QXmlStreamWriter writer(&file);

	writer.setAutoFormatting(true);
	writer.writeStartDocument();
	writer.writeStartElement("FSpriteDesigner");
	writer.writeAttribute("version","v1.0");
    writer.writeAttribute("type","FSpriteMorph");
	writer.writeAttribute("name",sprite->getName().c_str());
	writer.writeAttribute("id",sprite->getID().c_str());

	for(int i=0;i<sprite->getAnimationNu();i++)
	{
		DsAnimation* animation=sprite->getAnimation(i);
		writer.writeStartElement("animation");
		writer.writeAttribute("name",animation->getName().c_str());
		DsAnimation::Iterator iter;
		for(iter=animation->begin();iter!=animation->end();iter++)
		{
			DsFrame* frame=(*iter);
			writer.writeStartElement("frame");
			writer.writeAttribute("id",QString::number(frame->getFrameId()));
			if(frame->getType()==DsFrame::FRAME_KEY)
			{
				writer.writeAttribute("type","key");
				DsKeyFrame* key_frame=(DsKeyFrame*)frame;
				DsKeyFrame::Iterator iter=key_frame->begin();
				for(;iter!=key_frame->end();++iter)
				{
					DsFrameImage* image=*iter;
					writer.writeStartElement("frameimage");
					writer.writeTextElement("url",image->getImage()->name.c_str());
					writer.writeTextElement("posx",QString::number(image->getPosX()));
					writer.writeTextElement("posy",QString::number(image->getPosY()));
					writer.writeTextElement("scalex",QString::number(image->getScaleX()));
					writer.writeTextElement("scaley",QString::number(image->getScaleY()));
					writer.writeTextElement("angle",QString::number(image->getAngle()));

					float ax0,ay0,ax1,ay1;
					image->getTextureArea(&ax0,&ay0,&ax1,&ay1);

					writer.writeTextElement("areax0",QString::number(ax0));
					writer.writeTextElement("areay0",QString::number(ay0));
					writer.writeTextElement("areax1",QString::number(ax1));
					writer.writeTextElement("areay1",QString::number(ay1));
					writer.writeEndElement();
				}
			}
			else 
			{
				writer.writeAttribute("type","tween");
			}
			writer.writeEndElement();
		}
		writer.writeEndElement();
	}

    writer.writeEndElement();

    return true;

}





















