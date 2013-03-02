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

float DsUtil::clamp(float value,float min,float max)
{
    if(value<min) return min;
    if(value>max) return max;
    return value;
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
    if(!file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text))
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
    writer.writeStartElement("sprites");

    for(int i=0;i<proj->getSpriteNu();i++)
    {
        DsSprite* sprite=proj->getSprite(i);
        std::string spriteName=std::string("sprites/")+sprite->getName()+"-"+sprite->getID();
        writer.writeStartElement("sprite");
        writer.writeAttribute("url",spriteName.c_str());
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
    if(!file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text))
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
                    std::string url=image->getImage()->name;
                    std::string rel_url;
                    unsigned int i;
                    for(i=0;i<url.length();i++)
                    {
                        if(url[i]!=dir_name[i])
                        {
                            break;
                        }
                    }
                    rel_url=url.c_str()+i;

                    writer.writeTextElement("url",rel_url.c_str());
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

                    float fx,fy;
                    fx=image->getOffsetX();
                    fy=image->getOffsetY();

                    writer.writeTextElement("offsetx",QString::number(fx));
                    writer.writeTextElement("offsety",QString::number(fy));

                    float alpha=image->getAlpha();
                    writer.writeTextElement("alpha",QString::number(alpha));

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

void s_writeTab(QFile& file,int num)
{
    for(int i=0;i<num;i++)
    {
        file.write("\t");
    }
}
int  s_getResourcePos(const std::vector<DsImage*>& resources,DsImage* image)
{
    for(unsigned int i=0;i<resources.size();i++)
    {
        if(resources[i]==image)
        {
            return i;
        }
    }
    return -1;
}


bool DsUtil::exportSprite(DsSprite* sprite,QFile& file)
{
    std::string buf;
    QString qbuf;
    file.write("version:\"v1.0\"\n");
    file.write("type:\"sprite2d\"\n");

    buf=std::string("name:\"")+sprite->getName()+"\"\n";
    file.write(buf.c_str());

    std::vector<DsImage*> resources;

    for(unsigned int i=0;i<sprite->getAnimationNu();i++)
    {
        DsAnimation* anim=sprite->getAnimation(i);
        DsAnimation::Iterator frame_iter;
        for(frame_iter=anim->begin();frame_iter!=anim->end();++frame_iter)
        {
            DsFrame* frame=*frame_iter;
            if(frame->getType()==DsFrame::FRAME_KEY)
            {
                DsKeyFrame* key_frame=(DsKeyFrame*) frame;
                for(unsigned int j=0;j<key_frame->getFrameImageNu();j++)
                {
                    DsFrameImage* f_image=key_frame->getFrameImage(j);
                    if(s_getResourcePos(resources,f_image->getImage())==-1)
                    {
                        resources.push_back(f_image->getImage());
                    }
                }
            }
        }
    }

    file.write("resources:[\n");
    for(unsigned int i=0;i<resources.size();i++)
    {
        s_writeTab(file,1);
        file.write("{\n");
        DsImage* image=resources[i];
        s_writeTab(file,2);
        file.write("embed:\"false\"\n");
        /*
            QSize size=image->size();
            qbuf=QString("width:")+QString::number(size.width())+QString("\n");
            file.write(qbuf.toStdString().c_str());
            qbuf=QString("height:")+QString::number(size.height())+QString("\n");
            */
        s_writeTab(file,2);
        //buf=std::string("url:\"")+image->getPathRelativeToProject()+std::string("\"\n");
        buf=std::string("url:\"")+image->name+std::string("\"\n");
        file.write(buf.c_str());

        s_writeTab(file,1);
        file.write("},\n");
    }
    file.write("]\n");
    return true;
}










































