#ifndef _DS_UTIL_H_
#define _DS_UTIL_H_
#include <QString>
#include <string>

#include "model/DsModel.h"

class DsUtil
{
	public:
		static std::string integerToHexStr(long value);
		static QString stoq(const std::string str);
		static std::string qtos(const QString& q);
		static std::string uniqueStringID();
		static bool makeDirExist(const std::string& dir);
    public:
        static DsProject* loadProject(const std::string& dir_name,const std::string& file_name,std::string& msg);
        static bool saveProject(DsProject* proj);
        static bool saveProjectFile(DsProject* proj);
        static bool saveSpriteFile(const std::string& dir_name,const std::string& file_name,DsSprite* sprite);
};

#endif /*_DS_UTIL_H_*/

