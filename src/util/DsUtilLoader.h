#ifndef _DS_UTIL_LOADER_H_
#define _DS_UTIL_LOADER_H_
#include <string>
#include <QtXml>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <string>

#include "model/DsModel.h"

class  DsProjectLoader 
{
	public:
		DsProjectLoader(const std::string& dir,const std::string& file);
		DsProject* loadProject();
		std::string getLogMsg(){return m_logMsg;}
	private:
		std::string m_logMsg;
		std::string m_dir;
		std::string m_file;
};
class DsSpriteLoader
{
	public:
        DsSpriteLoader(const std::string& dir,const std::string& file);
		DsSprite* loadSprite();
		std::string getLogMsg(){return m_logMsg;}
	protected:
		DsAnimation* loadAnimation(QDomNode& node);
		DsFrame* loadFrame(QDomNode& node);
		DsFrameImage* loadFrameImage(QDomNode& node);
	private:
		std::string m_logMsg;
		std::string m_dir;
		std::string m_file;
};
#endif /*_DS_UTIL_LOADER_H_*/


