#ifndef _CBUFFTABLE_H_
#define _CBUFFTABLE_H_

#include "obj_mTable.h"
#include "CBuffInfoLoader.h"

typedef ObjTable<CBuff*, CBuffInfoLoader> BUFF_INFO;

class CBuffTable:public BUFF_INFO
{
public:
	static void initCBuffTable();
	float getSurplus();
	void create(unsigned int id);
	bool afterTime(float timePass);
	CBuffTable();
	~CBuffTable();

private:
	float m_fSurplus;
};

#endif