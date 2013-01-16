#ifndef _CMONSTERINFOLOADER_H_
#define _CMONSTERINFOLOADER_H_

#include "CMonsterInfo.h"

class CMonsterInfoLoader
{
public:
    CMonsterInfo* create(int type);
};

#endif