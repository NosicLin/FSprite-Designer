#ifndef _DS_SPRITE_UTIL_H_
#define _DS_SPRITE_UTIL_H_
#include <QtXml>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>

#include <string>
#include "model/DsModel.h"


class DsSpriteUtil
{
public:
    static DsProject* loadProject(const std::string& path);
    static void saveProject(DsProject* proj,const std::string& path);

protected:
    static DsFrame* loadFrame(QDomNode node);
    static DsAnimation* loadAnimation(QDomNode node);
    static DsFrameImage* loadFrameImage(QDomNode node);
	static void writeFrame(DsFrame* frame,QXmlStreamWriter& writer);
	static void writeFrameImage(DsFrameImage* image,QXmlStreamWriter& writer);
	static void writeAnimation(DsAnimation* image,QXmlStreamWriter& writer);

};
#endif /*_DS_SPRITE_UTIL_H_*/


