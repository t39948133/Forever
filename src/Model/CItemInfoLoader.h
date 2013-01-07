#ifndef _CITEMINFOLOADER_H_
#define _CITEMINFOLOADER_H_

#include "CItemInfo.h"

class CItemInfoLoader
{
public:
	CItemInfo* create (int type);
	bool isWeapon(int type);		//檢查是否武器
	bool isArmor(int type);			//檢查是否防具
	bool isConsumable(int type);	//檢查是否消耗物品

} ;




#endif