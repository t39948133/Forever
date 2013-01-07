#ifndef _CBACKPACK_H_
#define _CBACKPACK_H_

#include "CItem.h"
#include "Common.h"

class CBackPack
{
public:
	void setGrid(int grid, CItem& itm);		//設定格中內容是什麼(net pack使用)
	CItem* getItem(int grid);					//取得這格內容
    CItemInfo* getCItem(int grid);                       //取得這格內容
	void addItem(int id, int& stack, int& grid);	//增加物品 id 物品編號 stack 數量 

	void initBack();								//預設角色建立有的物品

private:
	CItem m_itemBack[BACK_MAX];

};


#endif