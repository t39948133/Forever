#include "CNPCInfo.h"

void CNPCInfo::initNPCInfo(std::string name, std::string meshName,
									std::vector<std::string> talk, NPCType type,
									std::vector<int> viQuest, std::vector<int> viSell)
{
	m_strName = name;
	m_strMeshName = meshName;
	m_vstrTalk = talk;
	m_workType = type;
	m_viQuest = viQuest;
	m_viSell = viSell;
}

std::string CNPCInfo::getName()
{
	return m_strName;
}

std::string CNPCInfo::getMeshName()
{
	return m_strMeshName;
}

std::string CNPCInfo::getTalk()
{
	int offset = rand() % m_vstrTalk.size();
	return m_vstrTalk[offset];
}

NPCType CNPCInfo::getNPCType()
{
	return m_workType;
}

std::vector<int> CNPCInfo::getvQuest()
{
	return m_viQuest;
}

std::vector<int> CNPCInfo::getSell()
{
	return m_viSell;
}

NPCClassType CNPCInfo::getClassType()
{
	return NPC;
}

void CNPCInfo::read(FILE *pFile)
{
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CNPCInfo::write(FILE *pFile)
{
}
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_