#include "CArmorInfo.h"

ArmorWearType CArmorInfo::getWear()
{
	return m_wear;
}

void CArmorInfo::initArmorInfo(std::string name, std::string iconName, ItemType type, bool soulBind,
                           char level, int stackLimit, int sellPrice, int buyPrice,
                           EquipQuality quality, AdvancedAttribute baseAttr,
                           AdvancedAttribute extendAttr, ArmorWearType wear)
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
	m_wear = wear;
}

CArmorInfo::~CArmorInfo()
{
}

ItemClassType CArmorInfo::getClassType ()
{
	return ARMOR;
}

void CArmorInfo::read(FILE* pFile)
{
	CEquipInfo::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_wear, sizeof(m_wear), 1, pFile);
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CArmorInfo::write(FILE* pFile)
{
	CEquipInfo::write(pFile);
	int version = 0;
	fwrite (&version, sizeof(version), 1, pFile);

	fwrite (&m_wear, sizeof(m_wear), 1, pFile);
}

#endif //#ifdef _GAMEENGINE_2D_EDITOR_
