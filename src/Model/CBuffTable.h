#ifndef _CBUFFTABLE_H_
#define _CBUFFTABLE_H_

#include "obj_mTable.h"
#include "CBuffInfoLoader.h"

typedef ObjTable<CBuff*, CBuffInfoLoader> BUFF_INFO;

class CBuffTable:public BUFF_INFO
{
public:
	static void initCBuffTable();   //初始
	float getSurplus(); //取得持續時間
	void create(unsigned int id);   //設定成某一個
	bool afterTime(float timePass); //更新時間
	CBuffTable();
	~CBuffTable();

private:
	float m_fSurplus;   //持續時間
};

#endif