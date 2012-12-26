#ifndef _CWEAPON_H_
#define _CWEAPON_H_

#include "CEquip.h"

class CWeapon:public CEquip		//武器
{
public:
	WeaponWieldType getWield();
	void initWeapon(std::string name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, WeaponWieldType wield);
	
	~CWeapon();
	int getClassType ();

	void read(FILE* pFile);

private:
	WeaponWieldType m_wield;	//拿取方式
};



#endif