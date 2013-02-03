#include "DsUtil.h"


QString DsUtil::stoq(const std::string str)
{
	return QString(str.c_str());
}

std::string DsUtil::qtos(const QString& q)
{
    return std::string(q.toLatin1().data());
}
