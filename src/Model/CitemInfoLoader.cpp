#include "CItemInfoLoader.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"

CItemInfo* CItemInfoLoader::create (int type)
{
	if(type == WEAPON)
	{
		return new CWeaponInfo();
	}
	else if(type == ARMOR)
	{
		return new CArmorInfo() ;
	}
	else if(type == CONSUMABLE)
	{
		return new CConsumableInfo();
	}
	else
	{
		return NULL;
	}
}

bool CItemInfoLoader::isWeapon(int type)
{
	if(type == DAGGER || type == SWORD || type == MACE || type == STAVE || 
		type == SPELLBOOK || type == ORB || type == GREATSWORD || type == POLEARM ||
		type == BOW || type == SHIELDS)
	{
		return true;
	}
	return false;
}

bool CItemInfoLoader::isArmor(int type)
{
	if(type == CLOTH || type == LEATHER || type == CHAIN || type == PLATE)
	{
		return true;
	}
	return false;
}

bool CItemInfoLoader::isConsumable(int type)
{
	if(type == POTION || type == FOOD || type == SCROLL)
	{
		return true;
	}
	return false;
}