#include <QMessageBox>

#include "DsUtilLoader.h"
#include "util/DsUtil.h"
#include "util/DsDebug.h"


DsProjectLoader::DsProjectLoader(const std::string& dir,const std::string& file)
{
	m_logMsg="";
	m_dir=dir;
	m_file=file;
}

DsProject* DsProjectLoader::loadProject()
{
    std::string file_path=m_dir+m_file;
    QFile file(file_path.c_str());
	if(!file.open(QFile::ReadOnly|QFile::Text))
	{
		m_logMsg="Open File Failed";
		return NULL;
	}

	QDomDocument xml_doc;
	QString errstr;
	int errline,errcol;
	if(!xml_doc.setContent(&file,false,&errstr,&errline,&errcol))
	{
		errstr=errstr+
			QString("(")+
		   	QString::number(errline)+
			QString(",")+ 
			QString::number(errcol)+QString(")");

		m_logMsg=errstr.toStdString();
		return NULL;
	}

	QDomElement elm_root=xml_doc.documentElement();
	if(elm_root.nodeName()!=QString("FSpriteDesigner"))
	{
		m_logMsg="Err File Type";
		return NULL;
	}

	if(elm_root.attribute("version")!=QString("v1.0"))
	{
		m_logMsg="version not support";
		return NULL;
	}
	if(elm_root.attribute("type")!=QString("FSpriteProject"))
	{
		m_logMsg="Error File:Not FSpriteDesigner Project File";
		return NULL;
	}


	DsProject* proj=new DsProject;
	proj->setFileName(m_file);
	proj->setDirName(m_dir);

	QDomElement elm_sprites=elm_root.firstChildElement("sprites");
	QDomNodeList nl_sprite=elm_sprites.elementsByTagName("sprite");

	for(int i=0;i<nl_sprite.count();i++)
	{
		QDomNode dn_sprite=nl_sprite.item(i);
        QDomElement elm_sprite=dn_sprite.toElement();

        std::string url=elm_sprite.attribute("url").toStdString();
		DsSpriteLoader loader(m_dir,url);
        DsSprite* sprite=loader.loadSprite();

		if(sprite==NULL)
		{
            QMessageBox::information(NULL,"loadProject",
                    QString("Load Sprites Failed(")+url.c_str()+"):"+loader.getLogMsg().c_str(),
                    QMessageBox::Yes
                    ) ;
		}
		else 
		{
			proj->addSprite(sprite);
		}
	}
	return proj;
}


DsSpriteLoader::DsSpriteLoader(const std::string& dir,const std::string& file)
{
	m_logMsg="";
	m_dir=dir;
	m_file=file;
}

DsSprite* DsSpriteLoader::loadSprite()
{
    std::string file_path=m_dir+m_file;
    QFile file(file_path.c_str());
	if(!file.open(QFile::ReadOnly|QFile::Text))
	{
		m_logMsg="Open File Failed";
		return NULL;
	}

	QDomDocument xml_doc;
	QString errstr;
	int errline,errcol;
	if(!xml_doc.setContent(&file,false,&errstr,&errline,&errcol))
	{
		errstr=errstr+
			QString("(")+
		   	QString::number(errline)+
			QString(",")+ 
			QString::number(errcol)+QString(")");

		m_logMsg=errstr.toStdString();
		return NULL;
	}

	QDomElement elm_root=xml_doc.documentElement();
	if(elm_root.nodeName()!=QString("FSpriteDesigner"))
	{
		m_logMsg="Err File Type";
		return NULL;
	}

	if(elm_root.attribute("version")!=QString("v1.0"))
	{
		m_logMsg="version not support";
		return NULL;
	}
    if(elm_root.attribute("type")!=QString("FSpriteMorph"))
	{
		m_logMsg="Error File:Not FSpriteDesigner Project File";
		return NULL;
	}

	std::string sp_name=elm_root.attribute("name").toStdString();
	std::string sp_id=elm_root.attribute("id").toStdString();

	DsSprite* sprite=new DsSprite;

	sprite->setName(sp_name);
	sprite->setID(sp_id);

    QDomNodeList anims=elm_root.elementsByTagName("animation");
    for(int i=0;i<anims.count();i++)
    {
        QDomNode node=anims.item(i);
        DsAnimation* anim=loadAnimation(node);
		if(anim!=NULL)
		{
			sprite->addAnimation(anim);
		}
    }
    return sprite;
}

DsAnimation* DsSpriteLoader::loadAnimation(QDomNode& node)
{
	QDomElement element=node.toElement();
	QString anim_name=element.attribute("name");
    DsAnimation* anim=new DsAnimation(DsUtil::qtos(anim_name));

	QDomNodeList frames=element.childNodes();
	for(int i=0;i<frames.count();i++)
	{
		QDomNode f=frames.item(i);
        DsFrame* ds_frame=loadFrame(f);
		if(ds_frame!=NULL)
		{
			anim->pushFrame(ds_frame);
		}
	}
	return anim;
}
DsFrame* DsSpriteLoader::loadFrame(QDomNode& node)
{
	QDomElement element=node.toElement();
	int frame_id=element.attribute("id").toInt();
	QString frame_type=element.attribute("type");
    if(frame_type=="key")
	{
		DsKeyFrame* f=new DsKeyFrame(frame_id);
		QDomNodeList images=element.childNodes();
		for(int i=0;i<images.count();i++)
        {
            QDomNode node=images.item(i);
            DsFrameImage* img=loadFrameImage(node);
			if(img)
			{
				f->pushFrameImage(img);
			}
		}
		return  f;
	}
	else if(frame_type=="tween")
	{
        return new DsTweenFrame(NULL,NULL,frame_id);
	}
	else 
    {
        DsDebug<<"UnKown Frame Type,Ingnore"<<endl;
        return NULL;
	}
}

DsFrameImage* DsSpriteLoader::loadFrameImage(QDomNode& node)
{
    float tx=0,ty=0,sx=1,sy=1,angle=0;
    float areax0=0,areay0=0,areax1=1,areay1=1;
    float offsetx,offsety;
    float alpha;
    std::string url;
    tx=node.firstChildElement("posx").text().toFloat();
    ty=node.firstChildElement("posy").text().toFloat();
    sx=node.firstChildElement("scalex").text().toFloat();
    sy=node.firstChildElement("scaley").text().toFloat();
    angle=node.firstChildElement("angle").text().toFloat();

    areax0=node.firstChildElement("areax0").text().toFloat();
    areay0=node.firstChildElement("areay0").text().toFloat();
    areax1=node.firstChildElement("areax1").text().toFloat();
    areay1=node.firstChildElement("areay1").text().toFloat();

    offsetx=node.firstChildElement("offsetx").text().toFloat();
    offsety=node.firstChildElement("offsety").text().toFloat();
    alpha=node.firstChildElement("alpha").text().toFloat();

    url=node.firstChildElement("url").text().toStdString();

    //DsFrameImage* ret=DsFrameImage::create(m_dir+url);
    DsFrameImage* ret=DsFrameImage::create(url);
    ret->setPos(tx,ty);
    ret->setAngle(angle);
    ret->setScale(sx,sy);
    ret->setTextureArea(areax0,areay0,areax1,areay1);
    ret->setOffset(offsetx,offsety);
    ret->setAlpha(alpha);
    return ret;
}
















