#include "CSkillInfoLoader.h"

CSkillInfo* CSkillInfoLoader::create(int type)
{
    if(SKILL == type)
    {
        return new CSkillInfo();
    }
    else
    {
        return NULL;
    }
}