#include <QtOpenGL>
#include <QImage>
#include "DsResourceMgr.h"
#include "model/DsData.h"

static std::vector<DsImage*> s_resource;

DsImage* s_getResource(const std::string& name)
{
    for(int i=0;i<s_resource.size();i++)
    {
        if(s_resource[i]->name==name)
        {
            return s_resource[i];
        }
    }


    QImage* image=new QImage(QString(name.c_str()));

    if(image==NULL)
    {
        return NULL;
    }
   // image->convertToFormat(QImage::Format_ARGB32);

    DsImage* res=new DsImage(name,image,0);

    s_resource.push_back(res);
    return res;
}


DsImage* DsResourceMgr::loadImage(const std::string& name)
{
    DsImage* res=s_getResource(name);
    return res;
}




