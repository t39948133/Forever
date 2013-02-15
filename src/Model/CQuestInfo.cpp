#include "CQuestInfo.h"

CQuestInfo::CQuestInfo()
{
}

CQuestInfo::~CQuestInfo()
{
}

void CQuestInfo::initQuestInfo(std::string name, std::string desc, char level,
										 int perQuestID, QuestType eventType, int MonsterID,
										 int TalkID, int ItemID, int Const, std::vector<int> reware,
										 int xp, long long money)
{
	m_strName = name;
	m_strDesc = desc;
	m_Level = level;
	m_iPerQuestID = perQuestID;
	m_EventType = eventType;
	m_iMonsterID = MonsterID;
	m_iTalkID = TalkID;
	m_iItemID = ItemID;
	m_iConst = Const;
	m_viReware = reware;
	m_ixp = xp;
	m_Money = money;
}

std::string CQuestInfo::getName()
{
	return m_strName;
}

std::string CQuestInfo::getDesc()
{
	return m_strDesc;
}

char CQuestInfo::getLevel()
{
	return m_Level;
}

int CQuestInfo::getPerQuestID()
{
	return m_iPerQuestID;
}

QuestType CQuestInfo::getQuestType()
{
	return m_EventType;
}

int CQuestInfo::getMonsterID()
{
	return m_iMonsterID;
}

int CQuestInfo::getTalkID()
{
	return m_iTalkID;
}

int CQuestInfo::getItemID()
{
	return m_iItemID;
}

int CQuestInfo::getTragetID()
{
	switch(m_EventType)
	{
	case KILL:		//殺怪
		return m_iMonsterID;
		break;
	case TALK:		//對話
		return m_iTalkID;
		break;
	case TAKE:		//收集物品
		return m_iItemID;
		break;
	}
	return -1;
}

int CQuestInfo::getConst()
{
	return m_iConst;
}

std::vector<int> CQuestInfo::getItemReware()
{
	return m_viReware;
}

long long CQuestInfo::getMoney()
{
	return m_Money;
}

int CQuestInfo::getXP()
{
	return m_ixp;
}

void CQuestInfo::read(FILE *pFile)
{
	int version = 0;
	fread(&version, sizeof(version), 1, pFile);

	char buf[256];
	int nameSize = 0;
	fread(&nameSize, sizeof(nameSize), 1, pFile);
	memset(buf, 0, sizeof(buf));
	fread(buf, nameSize, 1, pFile);
	m_strName = buf;
	int descSize = 0;
	fread(&descSize, sizeof(descSize), 1, pFile);
	memset(buf, 0, sizeof(buf));
	fread(buf, descSize, 1, pFile);
	m_strDesc = buf;
	fread(&m_Level, sizeof(m_Level), 1, pFile);
	fread(&m_iPerQuestID, sizeof(m_iPerQuestID), 1, pFile);
	fread(&m_EventType, sizeof(m_EventType), 1, pFile);
	fread(&m_iMonsterID, sizeof(m_iMonsterID), 1, pFile);
	fread(&m_iTalkID, sizeof(m_iTalkID), 1, pFile);
	fread(&m_iItemID, sizeof(m_iItemID), 1, pFile);
	fread(&m_iConst, sizeof(m_iConst), 1, pFile);
	int rewareSize = 0;
	fread(&rewareSize, sizeof(rewareSize), 1, pFile);
	for(int i = 0; rewareSize > i; i++)
	{
		int ItemID = -1;
		fread(&ItemID, sizeof(ItemID), 1, pFile);
		m_viReware.push_back(ItemID);
	}
	fread(&m_ixp, sizeof(m_ixp), 1, pFile);
	fread(&m_Money, sizeof(m_Money), 1, pFile);
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CQuestInfo::write(FILE *pFile)
{
	int version = 0;
	fwrite(&version, sizeof(version), 1, pFile);

	int nameSize = m_strName.size();
	fwrite(&nameSize, sizeof(nameSize), 1, pFile);
	fwrite(m_strName.c_str(), nameSize, 1, pFile);
	int descSize = m_strDesc.size();
	fwrite(&descSize, sizeof(descSize), 1, pFile);
	fwrite(m_strDesc.c_str(), descSize, 1, pFile);
	fwrite(&m_Level, sizeof(m_Level), 1, pFile);
	fwrite(&m_iPerQuestID, sizeof(m_iPerQuestID), 1, pFile);
	fwrite(&m_EventType, sizeof(m_EventType), 1, pFile);
	fwrite(&m_iMonsterID, sizeof(m_iMonsterID), 1, pFile);
	fwrite(&m_iTalkID, sizeof(m_iTalkID), 1, pFile);
	fwrite(&m_iItemID, sizeof(m_iItemID), 1, pFile);
	fwrite(&m_iConst, sizeof(m_iConst), 1, pFile);
	int rewareSize = m_viReware.size();
	fwrite(&rewareSize, sizeof(rewareSize), 1, pFile);
	std::vector<int>::iterator preware = m_viReware.begin();
	while(m_viReware.end() != preware)
	{
		int ItemID = (*preware);
		fwrite(&ItemID, sizeof(ItemID), 1, pFile);
		preware++;
	}
	fwrite(&m_ixp, sizeof(m_ixp), 1, pFile);
	fwrite(&m_Money, sizeof(m_Money), 1, pFile);
}
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_

QuestClassType CQuestInfo::getClassType()
{
	return QUEST;
}