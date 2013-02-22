#ifndef _DS_UTIL_H_
#define _DS_UTIL_H_

#include <QString>
#include <string>

class DsUtil
{
	public:
		static std::string integerToHexStr(long value);
		static QString stoq(const std::string str);
		static std::string qtos(const QString& q);
		static std::string uniqueStringID();
};

#endif /*_DS_UTIL_H_*/

