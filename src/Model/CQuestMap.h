#ifndef _CQUESTMAP_H_
#define _CQUESTMAP_H_

#include "CQuest.h"
#include "CNPC.h"

class CQuestMap
{
public:
	CQuestMap();
	~CQuestMap();
	std::list<CQuest*>	getHaveQuest();
	std::vector<int>	getFinishQuestID();
	CQuest*				onTalk(int id);
	CQuest*				onKill(int	id);
	CQuest*				onTake(int	grid, CBackpack& backPack);
	CQuest*				addQuest(CNPC npc, int id, char level);
	void				delQuest(CQuest* pquest);
	void				delQuestID(int id);
	void				finishQuestID(int id);
	void				addQuest(CQuest *pQuest);
	bool				addQuest(int id, char level);
	bool				haveQuest(int id);
	bool				canTake(int id, char level);
	bool				isFinish(int id);
	QuestState			getQuestState(int id, char level);
private:
	std::list<CQuest*> m_lpQuest;
	std::vector<int>	m_viFinishID;
};

#endif