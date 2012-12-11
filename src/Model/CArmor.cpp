#include "CArmor.h"

ArmorWearType CArmor::getWear()
{
	return m_wear;
}

void CArmor::read(FILE* pFile)
{
	CEquip::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_wear, sizeof(m_wear), 1, pFile);
}

void CArmor::write(FILE* pFile)
{
	CEquip::write(pFile);
	int version = 0;
	fwrite (&version, sizeof(version), 1, pFile);

	fwrite (&m_wear, sizeof(m_wear), 1, pFile);
}

void CArmor::initWeapon(std::wstring name, ItemType type, bool soulBind,
				char level, int stackLimit, int sellPrice, int buyPrice,
				EquipQuality quality, AdvancedAttribute baseAttr,
				AdvancedAttribute extendAttr, ArmorWearType wear)
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
	m_wear = wear;
}
