#include"CBuffInfoLoader.h"

CBuff* CBuffInfoLoader::create(int type)
{
	if(BUFF == type)
	{
		return new CBuff();
	}
	else
	{
		return NULL;
	}
}