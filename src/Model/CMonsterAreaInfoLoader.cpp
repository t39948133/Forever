#include "CMonsterAreaInfoLoader.h"

CMonsterAreaInfo* CMonsterAreaInfoLoader::create(int type)
{
	if(MONSTERAREA == type)
	{
		return new CMonsterAreaInfo();
	}
	return NULL;
}