#include "CItem.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"
#include "AttributeSet.h"

void CItem::initItem ()
{
	if(ITEM_INFO::read("Item.la"))
	{
	}
	else
	{
		CWeaponInfo* pw;
		pw = new CWeaponInfo();
		AdvancedAttribute baseAttr;
		AdvancedAttribute extendAttr;
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);
		baseAttr.iATK = 20;
		baseAttr.iCRI = 10;
		baseAttr.iHIT = 5;
		extendAttr.iHP = 80;
		extendAttr.iMPMax = 8;
		pw->initWeaponInfo("長劍", "Weapon/Sword_C01", SWORD, true, 1, 1, 20, 50, COMMON,
			baseAttr, extendAttr, ONE_HAND);
		addInfo(pw);

		CArmorInfo* pa;
		pa = new CArmorInfo();
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);
		baseAttr.iATK = 10;
		baseAttr.iHIT = 7;
		extendAttr.iHP = 90;
		extendAttr.iMPMax = 0;
		pa->initArmorInfo("胸甲", "Armor/PL_Torso_C01", CLOTH, false, 10, 1, 10, 70, COMMON,
			baseAttr, extendAttr, CLOTHES);
		addInfo(pa);

		CConsumableInfo* pc = new CConsumableInfo();
		pc->initConsumableInfo("生命藥水", "Potion/HP02_1", POTION, false, 1, 10, 5, 10, "回復生命37點", EDIBLE_HP, 37);
      addInfo(pc);

      CConsumableInfo* pb = new CConsumableInfo();
		pb->initConsumableInfo("主神盔甲", "Scroll/Skillbook_01", SCROLL, false, 1, 1, 5, 10, "可以學習主神盔甲技能", EDIBLE_SKILL, 0);
      addInfo(pb);

      CConsumableInfo* pd = new CConsumableInfo();
		pd->initConsumableInfo("猛烈一擊", "Scroll/Skillbook_01", SCROLL, false, 1, 1, 5, 10, "可以學習猛烈一擊技能", EDIBLE_SKILL, 1);
      addInfo(pd);
	}

}
CItem::CItem ():m_iStack(0)
{
}

CItem::~CItem()
{
}

bool CItem::addStack (int id, int& st)
{
	if (checkID (id) == false)
		return false ;

	CItemInfo* pinfo = getInfo () ;
	if (pinfo == NULL)
	{
		//空格
		ITEM_INFO::create (id) ;
		pinfo = getInfo () ;
		if (pinfo != NULL)
		{
			if (st <= pinfo->getStackLimit())
			{
				m_iStack = st ;
				st = 0 ;
			}else
			{
				//滿了
				st = st-(pinfo->getStackLimit()) ;
				m_iStack = pinfo->getStackLimit() ;
			}
			return true ;
		}else
			return false ;
	}else
	{
		if (getID () == id)
		{
			//同一種,可以堆疊
			CItemInfo* pinfo = getInfo () ;
			if (m_iStack+st <= pinfo->getStackLimit())
			{
				//堆疊沒滿
				m_iStack += st ;
				st = 0 ;
				return true ;
			}else
			{
				//堆滿了
				st = m_iStack+st-pinfo->getStackLimit() ;
				m_iStack = pinfo->getStackLimit() ;
				return true ;
			}
		}else
		{
			//不同種
			return false ;
		}
	}
}

int CItem::getStack ()
{
	return m_iStack ;
}

void CItem::create (int id, int st)
{
	ITEM_INFO::create (id) ;

	CItemInfo* pinfo = getInfo () ;
	if (pinfo != NULL)
	{
		if (st < pinfo->getStackLimit() && st >= 1)
			m_iStack = st ;
		else
			m_iStack = pinfo->getStackLimit();
	}
}

void CItem::taken()
{
	m_iStack--;
	if(m_iStack <= 0)
	{
		clear();
	}
}