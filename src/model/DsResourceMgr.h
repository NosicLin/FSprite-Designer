#ifndef _DS_RESOURCE_MGR_H_
#define _DS_RESOURCE_MGR_H_
#include <QPixmap>
#include <string>

#include "DsData.h"

class DsResourceMgr
{
	public:
        static DsImage* loadImage(const std::string& name);
};

#endif /*_DS_RESOURCE_MGR_H_*/

