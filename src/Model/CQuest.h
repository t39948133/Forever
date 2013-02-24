#ifndef _CQUEST_H_
#define _CQUEST_H_

#include "CQuestInfoLoader.h"
#include "obj_mTable.h"
#include "CBackPack.h"

typedef ObjTable<CQuestInfo*, CQuestInfoLoader> QUEST_INFO;

class CQuest:public QUEST_INFO
{
public:
	CQuest();
	~CQuest();
	static void	initQuest();						//初始
	bool	create(int kindID);						//設定
	int		getConst();								//取得目前完成數量
	bool	canReply();								//取得是否完成
	bool	onKill(int id);							//更新殺怪任務資訊
	bool	getItem(int grid, CBackpack& backPack);	//更新取得物品資訊，傳入背包、更新了哪一格
	bool	onTalk(int id);							//更新對話任務
private:
	friend class CPacketQuestData;
	int		m_iConst;	//任務目標目前完成數量
	bool	m_bFinish;	//是否完成
};
#endif