#include <time.h>
#include "DsUtil.h"


QString DsUtil::stoq(const std::string str)
{
	return QString(str.c_str());
}

std::string DsUtil::qtos(const QString& q)
{
    return std::string(q.toLatin1().data());
}


std::string DsUtil::uniqueStringID()
{
	static int i=0;
    std::string f=integerToHexStr(i++);
    std::string n=integerToHexStr(time(NULL));
	return n+f;
}

std::string DsUtil::integerToHexStr(long value)
{
	char buf[9];
	buf[8]=0;
	for(int i=0;i<8;i++)
	{
		int v= (0xf)&(value>>i*4);
		if(v<=9)
		{
			buf[i]=v+'0';
		}
		else
		{
			buf[i]=v-10+'a';
		}
	}
	return std::string(buf);
}






