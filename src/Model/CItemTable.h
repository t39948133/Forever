#ifndef _CITEMTABLE_H_
#define _CITEMTABLE_H_

#include "obj_mTable.h"
#include "CItem.h"

typedef ObjTable <CItem*> ITEM_INFO;

class CItemTable:public ITEM_INFO
{
public:	
	static void initItemTable ();
	CItemTable ();
	~CItemTable();
	bool addStack (int id, int& st);
	int getStack ();
	void create (int id, int st);

private:
	int m_iStack;

};


#endif