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
	void			create(int areaID);
	int			getMonsterCount();
	int			getConstTime();
	bool			isClick(float fx, float fy);
	CMonsterArea();
	~CMonsterArea();
	void			work(CGameServer *pGameServer, CScene *pScene);
#ifdef _GAMEENGINE_2D_
	void			draw(HDC hdc);
#endif

private:
	int m_iMonsterCount;
	int m_iConstTime;
   std::vector<long long> m_vMonsterUID;
};

#endif //#ifndef _CMONSTEREA_H_