#include <QtOpenGL>
#include "DsResourceMgr.h"


class _DsResource
{
	_DsResource(const std::string _name,QPixmap* _image,int _tex)
	{
		name=_name;
		image=_image;
		texture=_tex;
	}

	std::string name;
	QPixmap* image;
	int texture;
};
static std::vector<_DsResource> s_resource;

_DsResource* s_getResource(const std::string& name)
{
	for(int i=0;i<s_resource.size();i++)
	{
		if(s_resource[i]->name=name)
		{
			return s_resource[i];
		}
	}


	QPixmap* image=new QPixmap(QString(name.c_str()));
	if(image==NULL)
	{
		return NULL;
	}
	int	texture=bindTexture(*image,GL_TEXTURE_2D);

	_DsResource* res=new _DsResource(name,image,texture);

	s_resource.push_back(res);
	return res;
}


QPixmap* DsResourceMgr::loadImage(const std::string& name)
{
	_DsResource* res=s_getResource(name);
	if(res!=NULL)
	{
		return res->image;
	}
}

int DsResourceMgr::loadTexture(const std::string& name)
{
	_DsResource* res=s_getResource(name);
	if(res!=NULL)
	{
		return res->texture;
	}
}



