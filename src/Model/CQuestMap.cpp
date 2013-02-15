#include "CQuestMap.h"

CQuestMap::CQuestMap()
{
}

CQuestMap::~CQuestMap()
{
}

std::list<CQuest*> CQuestMap::getHaveQuest()
{
	return m_lpQuest;
}

std::vector<int> CQuestMap::getFinishQuestID()
{
	return m_viFinishID;
}

CQuest* CQuestMap::onTalk(int id)
{
	std::list<CQuest*>::iterator pQuest = m_lpQuest.begin();
	while(m_lpQuest.end() != pQuest)
	{
		if((*pQuest)->onTalk(id))
		{
			return (*pQuest);
		}
		pQuest++;
	}
	return NULL;
}

CQuest* CQuestMap::onKill(int id)
{
	std::list<CQuest*>::iterator pQuest = m_lpQuest.begin();
	while(m_lpQuest.end() != pQuest)
	{
		if((*pQuest)->onKill(id))
		{
			return (*pQuest);
		}
		pQuest++;
	}
	return NULL;
}

CQuest* CQuestMap::onTake(int grid, CBackpack& backPack)
{
	std::list<CQuest*>::iterator pQuest = m_lpQuest.begin();
	while(m_lpQuest.end() != pQuest)
	{
		if((*pQuest)->getItem(grid, backPack))
		{
			return (*pQuest);
		}
		pQuest++;
	}
	return NULL;
}

CQuest* CQuestMap::addQuest(CNPC npc, int id, char level)
{
	std::vector<int> quest = npc.getInfo()->getQuest();
	std::vector<int>::iterator iquest = quest.begin();
	while(quest.end() != iquest)
	{
		if((*iquest) == id)
		{
			if(addQuest((*iquest), level))
			{
				return m_lpQuest.back();
			}
			return NULL;
		}
		iquest++;
	}
	return NULL;
}

void CQuestMap::delQuest(CQuest *pquest)
{
	std::list<CQuest*>::iterator pQuest = m_lpQuest.begin();
	while(m_lpQuest.end() != pQuest)
	{
		if((*pQuest) == pquest)
		{
			m_lpQuest.erase(pQuest);
			return;
		}
		pQuest++;
	}
}

void CQuestMap::delQuestID(int id)
{
	std::list<CQuest*>::iterator pQuest = m_lpQuest.begin();
	while(m_lpQuest.end() != pQuest)
	{
		if((*pQuest)->getID() == id)
		{
			m_lpQuest.erase(pQuest);
			return;
		}
		pQuest++;
	}
}

void CQuestMap::finishQuestID(int id)
{
	delQuestID(id);
	m_viFinishID.push_back(id);
}

bool CQuestMap::addQuest(int id, char level)
{
	if(canTake(id, level))
	{
		CQuest* pQuest = new CQuest();
		pQuest->create(id);
		m_lpQuest.push_back(pQuest);
		return true;
	}
	return false;
}

bool CQuestMap::haveQuest(int id)
{
	std::list<CQuest*>::iterator pQuest = m_lpQuest.begin();
	while(m_lpQuest.end() != pQuest)
	{
		if((*pQuest)->getID() == id)
		{
			return true;
		}
	}
	return false;
}

bool CQuestMap::canTake(int id, char level)
{
	if(haveQuest(id))
	{
		return false;
	}
	if(isFinish(id))
	{
		return false;
	}
	CQuestInfo* pInfo = CQuest::getInfo(id);
	if(pInfo->getPerQuestID() != -1)
	{
		if(isFinish(pInfo->getPerQuestID()) == false)
		{
			return false;
		}
	}
	if(pInfo->getLevel() > level)
	{
		return false;
	}
	return true;
}

bool CQuestMap::isFinish(int id)
{
	std::vector<int>::iterator pint = m_viFinishID.begin();
	while(m_viFinishID.end() != pint)
	{
		if((*pint) == id)
		{
			return true;
		}
		pint++;
	}
	return false;
}

QuestState CQuestMap::getQuestState(int id, char level)
{
	if(canTake(id, level))
	{
		return QUEST_CAN_TAKE;
	}
	if(isFinish(id))
	{
		return QUEST_FINISH;
	}
	if(haveQuest(id))
	{
		return QUEST_WORKING;
	}
	return QUEST_NULL;
}