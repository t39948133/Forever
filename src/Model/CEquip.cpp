#include "CEquip.h"

EquipQuality CEquip::getQuality()
{
	return m_quality;
}

AdvancedAttribute CEquip::getBaseAttr()
{
	return m_baseAttr;
}

AdvancedAttribute CEquip::getExtendAttr()
{
	return m_extendAttr;
}

void CEquip::setQuality(EquipQuality quality)
{
	m_quality = quality;
}
	
void CEquip::setBaseAttr(AdvancedAttribute baseAttr)
{
	m_baseAttr = baseAttr;
}

void CEquip::setExtendAttr(AdvancedAttribute extendAttr)
{
	m_extendAttr = extendAttr;
}

void CEquip::read(FILE* pFile)
{
	CItem::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_quality, sizeof(m_quality), 1, pFile);
	fread (&m_baseAttr, sizeof(m_baseAttr), 1, pFile);
	fread (&m_extendAttr, sizeof(m_extendAttr), 1, pFile);

}