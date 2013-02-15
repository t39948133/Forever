#ifndef _CNPCINFO_H_
#define _CNPCINFO_H_

#include "Common.h"
#include "CQuest.h"

const int talkSentence = 3;

class CNPCInfo
{
public:
	CNPCInfo();
	void					initNPCInfo(std::string name, std::string meshName,
		std::vector<std::string> talk, NPCType type, std::vector<int> vQuest,
		std::vector<int> viSell);
	std::string			getName();			//取得名稱
	std::string			getMeshName();		//取得檔案名稱
	std::string			getTalk();			//取得對話內容
	NPCType				getNPCType();		//取得是哪種NPC
	std::vector<int>	getQuest();		//取得擁有任務(ID)
	std::vector<int>	getSell();			//取得販賣物品(ID)

	NPCClassType		getClassType();
	void					read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void					write(FILE* pFile);
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_
private:
	std::string m_strName;							//名稱
	std::string	m_strMeshName;						//檔案名稱
	std::vector<std::string>	m_vstrTalk;		//對話
	NPCType		m_workType;							//任務 商店 閒聊 NPC
	std::vector<int>	m_viQuest;					//擁有任務
	std::vector<int>	m_viSell;					//販賣物品
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class DLGNPC;
#endif	//_GAMEENGINE_2D_EDITOR_
};

#endif