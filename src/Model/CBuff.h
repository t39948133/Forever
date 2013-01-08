#ifndef _CBUFF_H_
#define _CBUFF_H_

#include "obj_mTable.h"
#include "CBuffInfoLoader.h"

typedef ObjTable<CBuffInfo*, CBuffInfoLoader> BUFF_INFO;

class CBuff:public BUFF_INFO
{
public:
	static void initBuff();   //初始
	float getSurplus(); //取得持續時間
	void create(unsigned int id);   //設定成某一個
	bool afterTime(float timePass); //更新時間
    CBuff();
    ~CBuff();

private:
	float m_fSurplus;   //持續時間
};

#endif