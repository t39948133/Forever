#include "CWeapon.h"

WeaponWieldType CWeapon::getWield()
{
	return m_wield;
}

void CWeapon::initWeapon(std::string name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, WeaponWieldType wield)
{
	setName(name);
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

CWeapon::~CWeapon()
{
}

int CWeapon::getClassType ()
{
	return WEAPON;
}

void CWeapon::read(FILE* pFile)
{
	CEquip::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_wield, sizeof(m_wield), 1, pFile);
}