#include "CItemInfoLoader.h"
#include "CWeapon.h"
#include "CArmor.h"
#include "CConsumable.h"

CItem* CItemInfoLoader::create (int type)
{
	if(type == WEAPON)
	{
		return new CWeapon();
	}
	else if(type == ARMOR)
	{
		return new CArmor () ;
	}
	else if(type == CONSUMABLE)
	{
		return new CConsumable ();
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