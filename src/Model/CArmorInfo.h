#ifndef _CARMORINFO_H_
#define _CARMORINFO_H_

#include "CEquipInfo.h"

class CArmorInfo:public CEquipInfo	//防具
{
public:
	ArmorWearType getWear();
	void initArmorInfo(std::string name, std::string iconName, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, ArmorWearType wear);

	~CArmorInfo();
	ItemClassType getClassType ();

	void read(FILE* pFile);

private:
	ArmorWearType m_wear;	//裝備位置
};


#endif