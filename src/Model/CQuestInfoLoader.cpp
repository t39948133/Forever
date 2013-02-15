#include "CQuestInfoLoader.h"

CQuestInfo* CQuestInfoLoader::create(int type)
{
	if(QUEST == type)
	{
		return new CQuestInfo();
	}
	return NULL;
}