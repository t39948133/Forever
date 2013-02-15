#ifndef _CQUESTINFOLOADER_H_
#define _CQUESTINFOLOADER_H_

#include "CQuestInfo.h"

class CQuestInfoLoader
{
public:
	CQuestInfo* create(int type);
};

#endif