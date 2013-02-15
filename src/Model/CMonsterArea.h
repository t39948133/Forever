#ifndef _CMONSTERAREA_H_
#define _CMONSTERAREA_H_

#include "obj_mTable.h"
#include "CMonsterAreaInfoLoader.h"
class CScene;
class CGameServer;

typedef ObjTable <CMonsterAreaInfo*, CMonsterAreaInfoLoader> MONSTERAREA_INFO;

class CMonsterArea:public MONSTERAREA_INFO
{
public:
	static void initMonsterArea();
	void			create(int id);
	int			getMonsterCount();
	int			getConstTime();
	bool			isClick(float fx, float fy);
	CMonsterArea();
	~CMonsterArea();
	void			work(CGameServer& gameServer, CScene& scene);
	void			draw(HDC hdc);
private:
	int m_iMonsterCount;
	int m_iConstTime;
};

#endif //#ifndef _CMONSTEREA_H_