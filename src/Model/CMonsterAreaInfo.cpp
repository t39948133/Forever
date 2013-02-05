#include "CMonsterAreaInfo.h"

void CMonsterAreaInfo::initMonsterAreaInfo(int maxMonster, float fx, float fy,
														 float bornSize, int AddTime,
														 std::vector<int> viMonsterID)
{
	m_iMaxMonster = maxMonster;
	m_position.fX = fx;
	m_position.fY = fy;
	m_fBornSize = bornSize;
	m_fAddTime = AddTime;
	m_viMonsterID = viMonsterID;
}

int CMonsterAreaInfo::getMaxMonster()
{
	return m_iMaxMonster;
}

const FPOS& CMonsterAreaInfo::getPosition()
{
	return m_position;
}

float CMonsterAreaInfo::getBornSize()
{
	return m_fBornSize;
}

int CMonsterAreaInfo::getAddTime()
{
	return m_fAddTime;
}

std::vector<int> CMonsterAreaInfo::getBornMonsterID()
{
	return m_viMonsterID;
}

void CMonsterAreaInfo::read(FILE *pFile)
{
	int version = 0;
	fread(&m_iMaxMonster, sizeof(m_iMaxMonster), 1, pFile);
	fread(&m_position, sizeof(m_position), 1, pFile);
	fread(&m_fBornSize, sizeof(m_fBornSize), 1, pFile);
	fread(&m_fAddTime, sizeof(m_fAddTime), 1, pFile);
	int size = 0;
	fread(&size, sizeof(size), 1, pFile);
	for(int i = 0; size > i; i++)
	{
		int kindID = -1;
		fread(&kindID, sizeof(kindID), 1, pFile);
		m_viMonsterID.push_back(kindID);
	}
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CMonsterAreaInfo::write(FILE *pFile)
{
	int version = 0;
	fwrite(&m_iMaxMonster, sizeof(m_iMaxMonster), 1, pFile);
	fwrite(&m_position, sizeof(m_position), 1, pFile);
	fwrite(&m_fBornSize, sizeof(m_fBornSize), 1, pFile);
	fwrite(&m_fAddTime, sizeof(m_fAddTime), 1, pFile);
	int size = m_viMonsterID.size();
	fwrite(&size, sizeof(size), 1, pFile);
	for(int i = 0; size > i; i++)
	{
		fwrite(&m_viMonsterID[i], sizeof(m_viMonsterID[i]), 1, pFile);
	}
}
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

MonsterArea CMonsterAreaInfo::getClassType()
{
	return MONSTERAREA;
}