#include "CItem.h"
#include "CWeapon.h"
#include "CArmor.h"
#include "CConsumable.h"

std::string CItem::getName()
{
	return m_strName;
}

ItemType CItem::getItemType()
{
	return m_type;
}

bool CItem::getSoulBind()
{
	return m_bSoulBind;
}

char CItem::getLevel()
{
	return m_level;
}

int CItem::getStackLimit()
{
	return m_iStackLimit;
}

int CItem::getSellPrice()
{
	return m_iSellPrice;
}

int CItem::getBuyPrice()
{
	return m_iBuyPrice;
}

bool CItem::isWeapon()
{
	if(m_type == DAGGER || m_type == SWORD || m_type == MACE || m_type == STAVE || 
		m_type == SPELLBOOK || m_type == ORB || m_type == GREATSWORD || m_type == POLEARM ||
		m_type == BOW || m_type == SHIELDS)
	{
		return true;
	}
	return false;
}

bool CItem::isArmor()
{
	if(m_type == CLOTH || m_type == LEATHER || m_type == CHAIN || m_type == PLATE)
	{
		return true;
	}
	return false;
}

bool CItem::isConsumable()
{
	if(m_type == POTION || m_type == FOOD || m_type == SCROLL)
	{
		return true;
	}
	return false;
}

AdvancedItem* CItem::getAll()
{
	AdvancedItem *pItem = new AdvancedItem;
	pItem->name = getName();				//名稱
	pItem->type = getItemType();			//種類
	pItem->soulBind = getSoulBind();		//綁定
	pItem->level = getLevel();				//等級
	pItem->stackLimit = getStackLimit();	//堆疊上限
	pItem->sellPrice = getSellPrice();		//賣價
	pItem->buyPrice = getBuyPrice();		//買價

	return pItem;
}

void CItem::setName(std::string name)
{
	m_strName = name;
}

void CItem::setItemType(ItemType type)
{
	m_type = type;
}

void CItem::setSoulBind(bool soulBind)
{
	m_bSoulBind = soulBind;
}

void CItem::setLevel(char level)
{
	if(level<0)
		return;
	m_level = level;
}

void CItem::setStackLimit(int stackLimit)
{
	if(stackLimit<0)
		return;
	m_iStackLimit = stackLimit;
}

void CItem::setSellPrice(int sellPrice)
{
	if(sellPrice<0)
		return;
	m_iSellPrice = sellPrice;
}

void CItem::setBuyPrice(int buyPrice)
{
	if(buyPrice<0)
		return;
	m_iBuyPrice = buyPrice;
}

void CItem::read(FILE* pFile)
{
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_strName, sizeof(m_strName), 1, pFile);

	fread (&m_type, sizeof(m_type), 1, pFile);
	fread (&m_bSoulBind, sizeof(m_bSoulBind), 1, pFile);
	fread (&m_level, sizeof(m_level), 1, pFile);
	fread (&m_iStackLimit, sizeof(m_iStackLimit), 1, pFile);
	fread (&m_iSellPrice, sizeof(m_iSellPrice), 1, pFile);
	fread (&m_iBuyPrice, sizeof(m_iBuyPrice), 1, pFile);

}