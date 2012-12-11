#include "CConsumable.h"


std::wstring CConsumable::getDesc()
{
	return m_strDesc;
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

void CConsumable::write(FILE* pFile)
{
	//CItem::write(pFile);
	int version = 0;
	fwrite (&version, sizeof(version), 1, pFile);

	fwrite (&m_strDesc, sizeof(m_strDesc), 1, pFile);
	fwrite (&m_effect, sizeof(m_effect), 1, pFile);
	fwrite (&m_iMuch, sizeof(m_iMuch), 1, pFile);
}

void CConsumable::initWeapon(std::wstring name, ItemType type, bool soulBind,
				char level, int stackLimit, int sellPrice, int buyPrice,
				std::wstring desc, EdibleEffectType effect, int much)
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
