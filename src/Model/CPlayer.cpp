#include "CPlayer.h"
#include "CItemTable.h"
#include "AttributeSet.h"

CPlayer::CPlayer(std::string strName, long long uid, char level) : CUnitObject(strName, uid, level), m_levelMax(50)
{
	m_backPack.initBack();
	upDateEquipAttr();
}

void CPlayer::addXP(unsigned int xp)
{
	m_xp += xp;
	if(m_xpMax < m_xp)	//取得經驗後 可升級
	{		
		m_xp -= m_xpMax;
		//升級function
	}
}

unsigned int CPlayer::getXP()
{
	return m_xp;
}

unsigned int CPlayer::getXPMax()
{
	return m_xpMax;
}

CBackPack CPlayer::getBackPack()
{
	return m_backPack;
}

void CPlayer::wearEquip(unsigned int id)
{
	CItem* pItem = CItemTable::getInfo(id);
	if(NULL == pItem)
	{
		return;
	}
	if(WEAPON == pItem->getClassType())
	{
		CWeapon* pWp;
		pWp = (CWeapon*) pItem;
		if(ONE_HAND == pWp->getWield())
		{
			wearToEquipSlot(MAIN_HAND, id);
		}
		else if(TWO_HAND == pWp->getWield())
		{
			wearToEquipSlot(OFF_HAND, id);
		}
		else
		{
			return;
		}
		
	}
	else if(pItem->getClassType() == ARMOR)
	{
		CArmor* pAm;
		pAm = (CArmor*) pItem;
		if(CLOTHES == pAm->getWear())
		{
			wearToEquipSlot(CHEST, id);
		}
		else if(BELTS == pAm->getWear())
		{
			wearToEquipSlot(BELT, id);
		}
		else if(PANTS == pAm->getWear())
		{
			wearToEquipSlot(LEGS, id);
		}
		else if(PAULDRONS == pAm->getWear())
		{
			wearToEquipSlot(SHOULDER, id);
		}
		else if(GLOVES == pAm->getWear())
		{
			wearToEquipSlot(GLOVE, id);
		}
		else if(BOOTS == pAm->getWear())
		{
			wearToEquipSlot(BOOT, id);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
	upDateEquipAttr();
}

void CPlayer::shedEquip(EquipSlot grid)
{
	if(m_mEquip.end() == m_mEquip.find(grid))
	{
		return;
	}
	int st = 1;
	int gr = 0;
	m_backPack.addItem(m_mEquip.find(grid)->second, st, gr);
	m_mEquip.erase(grid);
	upDateEquipAttr();
	//
}

void CPlayer::upDateEquipAttr()
{
	std::map<EquipSlot , int>::iterator pi = m_mEquip.begin();
	AdvancedAttribute advAttr;
	AttributeClear(advAttr);
	ObscureAttribute obsAttr;
	AttributeClear(obsAttr);
	BasisAttributeSet(getLevel(), getBasAttr(), advAttr, obsAttr);		//取得角色初始素質
	while (m_mEquip.end() != pi)
	{
		CWeapon* wp = (CWeapon*) CItemTable::getInfo(pi->second);
		if(NULL == wp)
		{
			break;
		}
		AttributeAdd (advAttr, wp->getBaseAttr());
		AttributeAdd (advAttr, wp->getExtendAttr());
		
		pi++;
	}
	setAdvAttr(advAttr);

    std::vector<CSkillTable>::iterator ps = m_vSkill.begin();
    while(m_vSkill.end() != ps)
    {
        ps->chackAvailable(getEquip());
        ps++;
    }
}

void CPlayer::wearToEquipSlot(EquipSlot es, unsigned int id)
{
	if(m_mEquip.end() == m_mEquip.find(es))
	{
		m_mEquip.insert(std::make_pair(es, id));
	}
	else
	{
		int st = 1;
		int bu = 0;
		m_backPack.addItem(m_mEquip.find(es)->second, st, bu);
		m_mEquip.insert(std::make_pair(es, id));
	}
}

std::map<EquipSlot, int> CPlayer::getEquip()
{
	return m_mEquip;
}
int CPlayer::getEquip(EquipSlot equip)
{
	int id ;
	if(m_mEquip.end() == m_mEquip.find(equip))
	{
		id = -1;
	}
	else
	{
		id = m_mEquip.find(equip)->second;
	}
	return id;
}