#include "CConsumableInfo.h"

std::string CConsumableInfo::getDesc()
{
	return m_strDesc;
}

EdibleEffectType CConsumableInfo::getEffect()
{
	return m_effect;
}
	
int CConsumableInfo::getMuch()
{
	return m_iMuch;
}

void CConsumableInfo::initConsumableInfo(std::string name, std::string iconName, ItemType type, bool soulBind,
				char level, int stackLimit, int sellPrice, int buyPrice,
				std::string desc, EdibleEffectType effect, int much)
{
	setName(name);
	seticonName(iconName);
	setItemType(type);
	setSoulBind(soulBind);
	setLevel(level);
	setStackLimit(stackLimit);
	setSellPrice(sellPrice);
	setBuyPrice(buyPrice);
	m_strDesc = desc;
	m_effect = effect;
	m_iMuch = much;
}

CConsumableInfo::~CConsumableInfo()
{
}

ItemClassType CConsumableInfo::getClassType ()
{
	return CONSUMABLE;
}

void CConsumableInfo::read(FILE* pFile)
{
    CItemInfo::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);
    char buf[longStrSize];
    fread(buf, sizeof(buf), 1, pFile);
    m_strDesc = buf;
	fread (&m_effect, sizeof(m_effect), 1, pFile);
	fread (&m_iMuch, sizeof(m_iMuch), 1, pFile);
}