#include"CBuffInfoLoader.h"

CBuffInfo* CBuffInfoLoader::create(int type)
{
	if(BUFF == type)
	{
		return new CBuffInfo();
	}
	else
	{
		return NULL;
	}
}