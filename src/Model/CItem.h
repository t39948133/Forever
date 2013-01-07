#ifndef _CITEM_H_
#define _CITEM_H_

#include "obj_mTable.h"
#include "CItemInfoLoader.h"

typedef ObjTable <CItemInfo*, CItemInfoLoader> ITEM_INFO;

class CItem:public ITEM_INFO
{
public:	
	static void initItem ();
	CItem ();
	~CItem();
	bool addStack (int id, int& st);
	int getStack ();
	void create (int id, int st);
	void taken();

private:
	int m_iStack;

};


#endif