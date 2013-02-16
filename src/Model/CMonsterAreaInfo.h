#ifndef _CMONSTERAREAINFO_H_
#define _CMONSTERAREAINFO_H_

#include "Common.h"

class CMonsterAreaInfo
{
public:
	void					initMonsterAreaInfo(int maxMonster, float fx, float fy, float bornSize,
		                                   int AddTime, std::vector<int> viMonsterID);	//初始
	int					getMaxMonster();					//取得最大出生量
	const FPOS&			getPosition();						//取得出生點
	float					getBornSize();						//取得範圍
	int					getAddTime();						//多久生一次
	std::vector<int>	getBornMonsterID();				//取得會生的怪種類
	void					read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void					write(FILE* pFile);
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
	MonsterArea			getClassType();

private:
	int					m_iMaxMonster;		//最大數量
	FPOS					m_position;			//出生點
	float					m_fBornSize;		//範圍區
	int					m_fAddTime;			//多久生一次
	std::vector<int>	m_viMonsterID;		//會生的怪
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class DLGMonsterArea;
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
};

#endif //#ifndef _CMONSTERAREAINFO_H_