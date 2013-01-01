#ifndef _CSKILLINFOLOADER_H_
#define _CSKILLINFOLOADER_H_

#include "CSkill.h"

class CSkillInfoLoader
{
public:
    CSkill* create(int type);
};

#endif