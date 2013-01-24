#ifndef _CWEAPONINFO_H_
#define _CWEAPONINFO_H_
#include "CEquipInfo.h"

//武器資訊
class CWeaponInfo : public CEquipInfo		
{
public:
	WeaponWieldType getWield();
	void initWeaponInfo(std::string name, std::string iconName, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, WeaponWieldType wield);
	
	~CWeaponInfo();
	ItemClassType getClassType ();

	void read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void write(FILE* pFile);
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

private:
	WeaponWieldType m_wield;	//拿取方式
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class WeaponPage;
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
};

#endif  // #ifndef _CWEAPONINFO_H_