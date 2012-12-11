#ifndef _CARMOR_H_
#define _CARMOR_H_

#include "CEquip.h"

class CArmor:public CEquip	//防具
{
public:
	ArmorWearType getWear();
	virtual void read(FILE* pFile);
	virtual void write(FILE* pFile);
	void initWeapon(std::wstring name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, ArmorWearType wear);

private:
	ArmorWearType m_wear;	//裝備位置
};


#endif