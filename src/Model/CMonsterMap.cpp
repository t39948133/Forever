#include "CMonsterMap.h"

CMonsterMap::CMonsterMap()
{
}

CMonsterArea* CMonsterMap::getArea(float fx, float fy)
{
	std::vector<CMonsterArea *>::iterator itArea = m_vMonsterArea.begin();
	while(itArea != m_vMonsterArea.end()) {
		if((*itArea)->isClick(fx, fy))
			return (*itArea);

		itArea++;
	}

	return NULL;
}

CMonsterArea* CMonsterMap::addArea()
{
	CMonsterArea *pArea = new CMonsterArea();
	m_vMonsterArea.push_back(pArea);
	return pArea;
}

void CMonsterMap::work(CGameServer *pGameServer, CScene *pScene)
{
	std::vector<CMonsterArea *>::iterator itArea = m_vMonsterArea.begin();
	while(itArea != m_vMonsterArea.end()) {
		(*itArea)->work(pGameServer, pScene);
		itArea++;
	}
}

#ifdef _GAMEENGINE_2D_
void CMonsterMap::draw(HDC hdc)
{
	std::vector<CMonsterArea *>::iterator itArea = m_vMonsterArea.begin();
	while(itArea != m_vMonsterArea.end()) {
		(*itArea)->draw(hdc);
		itArea++;
	}
}
#endif