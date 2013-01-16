#include "CMonsterInfoLoader.h"

CMonsterInfo* CMonsterInfoLoader::create(int type)
{
    if(MONSTER == type)
    {
        return new CMonsterInfo();
    }
    else
    {
        return NULL;
    }
}