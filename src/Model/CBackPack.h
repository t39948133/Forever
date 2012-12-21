#ifndef _CBACKPACK_H_
#define _CBACKPACK_H_

#include "CItemTable.h"
#include "Common.h"

class CBackPack
{
public:
	void setGrid(int grid, CItemTable& itm);		//設定格中內容是什麼(net pack使用)
	CItemTable* getItem(int grid);					//取得這格內容
	void addItem(int id, int& stack, int& grid);	//增加物品 id 物品編號 stack 數量 
													//grid 傳回最後放到哪個格子

	void initBack();								//預設角色建立有的物品

private:
	CItemTable m_itemBack[BACK_MAX];

};


#endif