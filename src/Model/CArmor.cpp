#include "CArmor.h"

ArmorWearType CArmor::getWear()
{
	return m_wear;
}

void CArmor::initArmor(std::string name, ItemType type, bool soulBind,
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

CArmor::~CArmor()
{
}

int CArmor::getClassType ()
{
	return ARMOR;
}

void CArmor::read(FILE* pFile)
{
	CEquip::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_wear, sizeof(m_wear), 1, pFile);
}