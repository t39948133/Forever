#include "CMonsterMap.h"

CMonsterMap::CMonsterMap()
{
}

CMonsterArea* CMonsterMap::getArea(float fx, float fy)
{
	std::vector<CMonsterArea*>::iterator pArea = m_vMonsterArea->begin();
	while(m_vMonsterArea->end() != pArea)
	{
		if((*pArea)->isClick(fx, fy))
		{
			return (*pArea);
		}
		pArea++;
	}
	return NULL;
}

CMonsterArea* CMonsterMap::addArea()
{
	CMonsterArea* pArea = new CMonsterArea();
	m_vMonsterArea->push_back(pArea);
	return m_vMonsterArea->back();
}

void CMonsterMap::work(CGameServer& gameServer,CScene& scene)
{
	std::vector<CMonsterArea*>::iterator pArea = m_vMonsterArea->begin();
	while(m_vMonsterArea->end() != pArea)
	{
		(*pArea)->work(gameServer, scene);
		pArea++;
	}
}

void CMonsterMap::draw(HDC hdc)
{
	std::vector<CMonsterArea*>::iterator pArea = m_vMonsterArea->begin();
	while(m_vMonsterArea->end() != pArea)
	{
		(*pArea)->draw(hdc);
		pArea++;
	}
}