#include "CSkillInfoLoader.h"

CSkill* CSkillInfoLoader::create(int type)
{
    if(SKILL == type)
    {
        return new CSkill();
    }
    else
    {
        return NULL;
    }
}