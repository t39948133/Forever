#include "CWeapon.h"

WeaponWieldType CWeapon::getWield()
{
	return m_wield;
}
/*
	void setName(std::wstring name);
	void setItemType(ItemType type);
	void setSoulBind(bool soulBind);
	void setLevel(char level);
	void setStackLimit(int stackLimit);
	void setSellPrice(int sellPrice);
	void setBuyPrice(int buyPrice);
		void setQuality(EquipQuality quality);
	void setBaseAttr(AdvancedAttribute baseAttr);
	void setExtendAttr(AdvancedAttribute extendAttr);
	void setWield(WeaponWieldType wield);
*/
void CWeapon::initWeapon(std::wstring name, ItemType type, bool soulBind,
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

void CWeapon::read(FILE* pFile)
{
	CEquip::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_wield, sizeof(m_wield), 1, pFile);
}

void CWeapon::write(FILE* pFile)
{
	CEquip::write(pFile);
	int version = 0;
	fwrite (&version, sizeof(version), 1, pFile);

	fwrite (&m_wield, sizeof(m_wield), 1, pFile);
}