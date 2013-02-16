#ifndef _CMONSTERMAP_H_
#define _CMONSTERMAP_H_

#include "CMonsterArea.h"

class CMonsterMap
{
public:
	CMonsterMap();
	void work(CGameServer *pGameServer, CScene *pScene);
	CMonsterArea* getArea(float fx, float fy);
	CMonsterArea* addArea();
#ifdef _GAMEENGINE_2D_
	void draw(HDC hdc);
#endif

private:
	std::vector<CMonsterArea *> m_vMonsterArea;
};

#endif