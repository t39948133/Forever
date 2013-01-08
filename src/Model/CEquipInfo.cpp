#include "CEquipInfo.h"

EquipQuality CEquipInfo::getQuality()
{
	return m_quality;
}

AdvancedAttribute CEquipInfo::getBaseAttr()
{
	return m_baseAttr;
}

AdvancedAttribute CEquipInfo::getExtendAttr()
{
	return m_extendAttr;
}

void CEquipInfo::setQuality(EquipQuality quality)
{
	m_quality = quality;
}
	
void CEquipInfo::setBaseAttr(AdvancedAttribute baseAttr)
{
	m_baseAttr = baseAttr;
}

void CEquipInfo::setExtendAttr(AdvancedAttribute extendAttr)
{
	m_extendAttr = extendAttr;
}

void CEquipInfo::read(FILE* pFile)
{
	CItemInfo::read(pFile);
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_quality, sizeof(m_quality), 1, pFile);
	fread (&m_baseAttr, sizeof(m_baseAttr), 1, pFile);
	fread (&m_extendAttr, sizeof(m_extendAttr), 1, pFile);
}