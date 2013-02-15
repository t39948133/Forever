#include "CQuest.h"

CQuest::CQuest():m_iConst(0)
{	
}

CQuest::~CQuest()
{
}

bool CQuest::create(int kindID)
{
	if(QUEST_INFO::checkID(kindID) == false)
	{
		return false;
	}
	if(QUEST_INFO::create(kindID))
	{
		CQuestInfo* pInfo = QUEST_INFO::getInfo();
		switch(pInfo->getQuestType())
		{
		case KILL:
		case TAKE:
			m_bFinish = false;
			return true;
			break;
		case TALK:
			m_bFinish = true;
			return true;
			break;
		}
	}
	return false;
}

int CQuest::getConst()
{
	return m_iConst;
}

bool CQuest::canReply()
{
	return m_bFinish;
}

void CQuest::initQuest()
{
	if(QUEST_INFO::read("quest.fla"))
	{
	}
	else
	{
		CQuestInfo* pquest = new CQuestInfo();
		std::vector<int> vireware;
		vireware.push_back(0);
		vireware.push_back(2);
		vireware.push_back(3);
		pquest->initQuestInfo("新手導引", "歡迎進入這遊戲，去和村長說話", 1, -1, TALK,
			-1, 0, -1, 0, vireware, 20, (long long) 100);
		QUEST_INFO::addInfo(pquest);
	}
}

bool CQuest::onKill(int id)
{
	CQuestInfo* pInfo = QUEST_INFO::getInfo();
	if(NULL == pInfo)
	{
		return false;
	}
	if(pInfo->getQuestType() != KILL)
	{
		return false;
	}
	if(pInfo->getMonsterID() == id)
	{
		m_iConst++;
		if(pInfo->getConst() == m_iConst)
		{
			m_bFinish = true;
		}
		return true;
	}
	return false;
}

bool CQuest::getItem(int grid, CBackpack& backPack)
{
	CQuestInfo* pInfo = QUEST_INFO::getInfo();
	if(NULL == pInfo)
	{
		return false;
	}
	if(pInfo->getQuestType() != TAKE)
	{
		return false;
	}
	CItem* pItem = backPack.getItem(grid);
	if(pInfo->getItemID() == pItem->getID())
	{
		m_iConst = pItem->getStack();
		if(pInfo->getConst() == m_iConst)
		{
			m_bFinish = true;
		}
		return true;	
	}
	
	return false;
}

bool CQuest::onTalk(int id)
{
	if(false == m_bFinish)
	{
		return false;
	}
	CQuestInfo* pInfo = QUEST_INFO::getInfo();
	if(NULL == pInfo)
	{
		return false;
	}
	if(pInfo->getTalkID() == id)
	{
		return true;
	}
	return false;
}