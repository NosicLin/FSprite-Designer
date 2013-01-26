#ifndef _DS_RESOURCE_MGR_H_
#define _DS_RESOURCE_MGR_H_
#include <QPixmap>
#include <string>

class DsResourceMgr
{
	public:
		static QPixmap* loadImage(const std::string& name);
		static int loadTexture(const std::string& name);
};

#endif /*_DS_RESOURCE_MGR_H_*/

