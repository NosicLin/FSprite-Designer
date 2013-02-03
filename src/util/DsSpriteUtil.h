#ifndef _DS_SPRITE_UTIL_H_
#define _DS_SPRITE_UTIL_H_
#include <QtXml>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>

#include <string>
#include "model/DsModel.h"

class DsSpriteUtil
{
public:
    static DsProject* loadProject(const std::string& path,std::string& msg);
    static std::string saveProject(DsProject* proj,const std::string& path);
protected:
    static DsFrame* loadFrame(QDomNode node);
    static DsAnimation* loadAnimation(QDomNode node);
    static DsFrameImage* loadFrameImage(QDomNode node);
};
#endif /*_DS_SPRITE_UTIL_H_*/


