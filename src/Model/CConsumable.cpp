#include "CConsumable.h"


std::string CConsumable::getDesc()
{
	return m_strDesc;
}

EdibleEffectType CConsumable::getEffect()
{
	return m_effect;
}
	
int CConsumable::getMuch()
{
	return m_iMuch;
}

void CConsumable::initConsumable(std::string name, ItemType type, bool soulBind,
				char level, int stackLimit, int sellPrice, int buyPrice,
				std::string desc, EdibleEffectType effect, int much)
{
	setName(name);
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

CConsumable::~CConsumable()
{
}

int CConsumable::getClassType ()
{
	return CONSUMABLE;
}

void CConsumable::read(FILE* pFile)
{
	//CItem::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_strDesc, sizeof(m_strDesc), 1, pFile);
	fread (&m_effect, sizeof(m_effect), 1, pFile);
	fread (&m_iMuch, sizeof(m_iMuch), 1, pFile);
}