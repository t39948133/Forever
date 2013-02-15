#include "CNPCInfoLoader.h"

CNPCInfo* CNPCInfoLoader::create(int type)
{
	if(NPC == type)
	{
		return new CNPCInfo();
	}
	return NULL;
}