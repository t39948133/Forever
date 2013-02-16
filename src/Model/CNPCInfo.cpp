#include "CNPCInfo.h"

CNPCInfo::CNPCInfo()
{
	srand((unsigned int)time(NULL));
}

void CNPCInfo::initNPCInfo(std::string name, std::string meshName,
									std::vector<std::string> talk, NPCType type,
									std::vector<int> vQuest, std::vector<int> viSell)
{
	m_strName = name;
	m_strMeshName = meshName;
	m_vstrTalk = talk;
	m_workType = type;
	m_viQuest = vQuest;
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

std::vector<int> CNPCInfo::getQuest()
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
	char buf[256];
	int version = 0;
	fread(&version, sizeof(version), 1, pFile);
	int nameSize = 0;
	fread(&nameSize, sizeof(nameSize), 1, pFile);
	memset(buf, 0, sizeof(buf));
	fread(buf, nameSize, 1, pFile);
	m_strName = buf;
	int meshNameSize = 0;
	fread(&meshNameSize, sizeof(meshNameSize), 1, pFile);
	memset(buf, 0, sizeof(buf));
	fread(buf, meshNameSize, 1, pFile);
	m_strMeshName = buf;
	for(int i = 0; talkSentence > i ; i++)
	{
		int talkSize = 0;
		fread(&talkSize, sizeof(talkSize), 1, pFile);
		memset(buf, 0, sizeof(buf));
		fread(buf, talkSize, 1, pFile);
		std::string strTalk;
		strTalk = buf;
		m_vstrTalk.push_back(strTalk);
	}
	memset(buf, 0, sizeof(buf));
	fread(&m_workType, sizeof(m_workType), 1, pFile);
	int questQuantity = -1;
	fread(&questQuantity, sizeof(questQuantity), 1, pFile);
	for(int i = 0; questQuantity > i ; i++)
	{
		int questID = -1;
		fread(&questID, sizeof(questID), 1, pFile);
		m_viQuest.push_back(questID);
	}
	int SellQuantity = -1;
	fread(&SellQuantity, sizeof(SellQuantity), 1, pFile);
	for(int i = 0; SellQuantity > i ; i++)
	{
		int SellItemID = -1;
		fread(&SellItemID, sizeof(SellItemID), 1, pFile);
		m_viSell.push_back(SellItemID);
	}
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CNPCInfo::write(FILE *pFile)
{
	int version = 0;
	fwrite(&version, sizeof(version), 1, pFile);
	int nameSize = m_strName.size();
	fwrite(&nameSize, sizeof(nameSize), 1, pFile);
	fwrite(m_strName.c_str(), nameSize, 1, pFile);
	int meshNameSize = m_strMeshName.size();
	fwrite(&meshNameSize, sizeof(meshNameSize), 1, pFile);
	fwrite(m_strMeshName.c_str(), meshNameSize, 1, pFile);
	std::vector<std::string>::iterator ptalk = m_vstrTalk.begin();
	while(m_vstrTalk.end() != ptalk)
	{
		int talkSize = ptalk->size();
		fwrite(&talkSize, sizeof(talkSize), 1, pFile);
		fwrite(ptalk->c_str(), talkSize, 1, pFile);
		ptalk++;
	}
	fwrite(&m_workType, sizeof(m_workType), 1, pFile);
	int questQuantity = m_viQuest.size();
	fwrite(&questQuantity, sizeof(questQuantity), 1, pFile);
	std::vector<int>::iterator pquest = m_viQuest.begin();
	while(m_viQuest.end() != pquest)
	{
		int questID = (*pquest);
		fwrite(&questID, sizeof(questID), 1, pFile);
		pquest++;
	}
	int SellQuantity = m_viSell.size();
	fwrite(&SellQuantity, sizeof(SellQuantity), 1, pFile);
	std::vector<int>::iterator psell = m_viSell.begin();
	while(m_viSell.end() != psell)
	{
		int SellItemID = (*psell);
		fwrite(&SellItemID, sizeof(SellItemID), 1, pFile);
		psell++;
	}
}
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_