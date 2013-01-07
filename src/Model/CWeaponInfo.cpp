#include "CWeaponInfo.h"

WeaponWieldType CWeaponInfo::getWield()
{
	return m_wield;
}

void CWeaponInfo::initWeaponInfo(std::string name, std::string iconName, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, WeaponWieldType wield)
{
	setName(name);
	seticonName(iconName);
	setItemType(type);
	setSoulBind(soulBind);
	setLevel(level);
	setStackLimit(stackLimit);
	setSellPrice(sellPrice);
	setBuyPrice(buyPrice);
	setQuality(quality);
	setBaseAttr(baseAttr);
	setExtendAttr(extendAttr);
	m_wield = wield;
}

CWeaponInfo::~CWeaponInfo()
{
}

ItemClassType CWeaponInfo::getClassType ()
{
	return WEAPON;
}

void CWeaponInfo::read(FILE* pFile)
{
	CEquipInfo::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_wield, sizeof(m_wield), 1, pFile);
}