#ifndef _CNPCINFO_H_
#define _CNPCINFO_H_

#include "Common.h"

const int talkSentence = 3;

class CNPCInfo
{
public:
	void					initNPCInfo(std::string name, std::string meshName,
		std::vector<std::string> talk, NPCType type, std::vector<int> viQuest,
		std::vector<int> viSell);
	std::string			getName();
	std::string			getMeshName();
	std::string			getTalk();
	NPCType				getNPCType();
	std::vector<int>	getvQuest();
	std::vector<int>	getSell();

	NPCClassType		getClassType();
	void					read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void					write(FILE* pFile);
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_
private:
	std::string m_strName;
	std::string	m_strMeshName;
	std::vector<std::string>	m_vstrTalk;
	NPCType		m_workType;
	std::vector<int>	m_viQuest;
	std::vector<int>	m_viSell;
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class DLGNPC
#endif	//_GAMEENGINE_2D_EDITOR_
};

#endif