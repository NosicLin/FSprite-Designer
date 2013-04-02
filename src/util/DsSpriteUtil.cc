#include <QtXml>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <string>

#include "model/DsModel.h"
#include "DsUtil.h"
#include "DsSpriteUtil.h"
#include "DsDebug.h"

void DsSpriteUtil::writeAnimation(DsAnimation* animation,QXmlStreamWriter& writer)
{
	writer.writeStartElement("animation");
	writer.writeAttribute("name",animation->getName().c_str());
	DsAnimation::Iterator iter;
	for(iter=animation->begin();iter!=animation->end();iter++)
	{
		writeFrame(*iter,writer);
	}
	writer.writeEndElement();
}
void DsSpriteUtil::writeFrame(DsFrame* frame,QXmlStreamWriter& writer)
{
	writer.writeStartElement("frame");
	writer.writeAttribute("id",QString::number(frame->getFrameId()));
	if(frame->getType()==DsFrame::FRAME_KEY)
	{
		writer.writeAttribute("type","key");

		DsKeyFrame* key_frame=(DsKeyFrame*)frame;
		DsKeyFrame::Iterator iter=key_frame->begin();
		for(;iter!=key_frame->end();++iter)
		{
			writeFrameImage(*iter,writer);
		}
	}
	else 
	{
		writer.writeAttribute("type","tween");
	}
	writer.writeEndElement();
}
void DsSpriteUtil::writeFrameImage(DsFrameImage* image,QXmlStreamWriter& writer)
{
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























