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

   // read m_strDesc {
   int descSize = 0;
   fread(&descSize, sizeof(descSize), 1, pFile);
   char buf[256];
   memset(buf, 0, sizeof(buf));
   fread(buf, descSize, 1, pFile);
   m_strDesc = buf;
   // } read m_strDesc

   fread (&m_effect, sizeof(m_effect), 1, pFile);
   fread (&m_iMuch, sizeof(m_iMuch), 1, pFile);
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CConsumableInfo::write(FILE* pFile)
{
   CItemInfo::write(pFile);
   int version = 0;
   fwrite (&version, sizeof(version), 1, pFile);

   // write m_strDesc {
   int descSize = m_strDesc.size();
   fwrite(&descSize, sizeof(descSize), 1, pFile);
   fwrite(m_strDesc.c_str(), m_strDesc.size(), 1, pFile);
   // } write m_strDesc

   fwrite (&m_effect, sizeof(m_effect), 1, pFile);
   fwrite (&m_iMuch, sizeof(m_iMuch), 1, pFile);
}
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
