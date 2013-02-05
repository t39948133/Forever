#ifndef _CMONSTERMAP_H_
#define _CMONSTERMAP_H_

#include "CMonsterArea.h"

class CMonsterMap
{
public:
	CMonsterMap();
	void work(long long& uid, CScene& scene);
	CMonsterArea* getArea(float fx, float fy);
	CMonsterArea* addArea();
	void draw(HDC hdc);
private:
	std::vector<CMonsterArea*> *m_vMonsterArea;
};

#endif