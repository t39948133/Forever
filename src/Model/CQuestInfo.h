#ifndef _CQUESTINFO_H_
#define _CQUESTINFO_H_

#include "Common.h"

class CQuestInfo
{
public:
	CQuestInfo();
	~CQuestInfo();
	void			initQuestInfo(std::string name, std::string desc, char level, int perQuestID,
		QuestType eventType, int MonsterID, int TalkID, int ItemID, int Const,
		std::vector<int> reware, int xp, long long money);
	std::string getName();					//取得名稱
	std::string getDesc();					//取得說明
	char			getLevel();					//取得承接等級
	int			getPerQuestID();			//取得前置任務
	QuestType	getQuestType();			//取得哪種任務目標
	int			getMonsterID();			//取得怪物ID
	int			getTalkID();				//取得說話對象ID
	int			getItemID();				//取得物品ID
	int			getTragetID();				//取得任務目標ID
	int			getConst();					//取得目標數量
	std::vector<int>	getItemReware();	//取得物品報酬
	int			getXP();						//取得經驗報酬
	long long	getMoney();					//取得金錢報酬

	void			read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void			write(FILE* pFile);
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_
	QuestClassType	getClassType();
private:
	std::string m_strName;			//名稱
	std::string m_strDesc;			//說明
	char			m_Level;				//承接等級
	int			m_iPerQuestID;		//前置任務ID
	QuestType	m_EventType;		//任務目標種類
	int			m_iMonsterID;		//怪物ID
	int			m_iTalkID;			//說話對象ID
	int			m_iItemID;			//物品ID
	int			m_iConst;			//達成目標數量
	std::vector<int> m_viReware;	//物品回報
	int			m_ixp;				//經驗回報
	long long	m_Money;				//金錢回報
};

#endif