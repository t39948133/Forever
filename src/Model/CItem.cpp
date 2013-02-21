#include "CItem.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"
#include "AttributeSet.h"

void CItem::initItem ()
{
   if(ITEM_INFO::read("../Item.fla") == false)
      ITEM_INFO::read("Item.fla");

	/*if(ITEM_INFO::read("Item.la"))
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
      baseAttr.fATKSpeed = 1.4f;
		baseAttr.iCRI = 10;
      baseAttr.iWDEF = 173;
		pw->initWeaponInfo("訓練用長劍", "Weapon/Sword_C01", "SW_C001.mesh", SWORD, false, 1, 1, 5, 20, COMMON,
			baseAttr, extendAttr, ONE_HAND);
		addInfo(pw);

		CArmorInfo* pa;
		pa = new CArmorInfo();
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);
      baseAttr.iDEF = 24;
      baseAttr.iFlee = 21;
		pa->initArmorInfo("訓練用金屬胸甲", "Armor/PL_Torso_C01", "LMCH_C101_Body.mesh", PLATE, false, 1, 1, 5, 20, COMMON,
			baseAttr, extendAttr, CLOTHES);
		addInfo(pa);

      pa = new CArmorInfo();
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);
      baseAttr.iDEF = 20;
      baseAttr.iFlee = 17;
		pa->initArmorInfo("訓練用金屬腿甲", "Armor/PL_Pants_C01", "LMCH_C101_Leg.mesh", PLATE, false, 1, 1, 5, 20, COMMON,
			baseAttr, extendAttr, PANTS);
		addInfo(pa);

		CConsumableInfo* pc = new CConsumableInfo();
		pc->initConsumableInfo("下級生命藥水", "Potion/HP02_2", POTION, false, 1, 200, 5, 100, "回復生命67點", EDIBLE_HP, 67);
      addInfo(pc);

      pc = new CConsumableInfo();
		pc->initConsumableInfo("下級精神藥水", "Potion/MP02_2", POTION, false, 1, 200, 5, 100, "回復精神98點", EDIBLE_MP, 98);
      addInfo(pc);

      
      pc = new CConsumableInfo();
		pc->initConsumableInfo("主神盔甲", "Scroll/Skillbook_01", SCROLL, false, 1, 1, 5, 10, "可以學習主神盔甲技能", EDIBLE_SKILL, 0);
      addInfo(pc);

      pc = new CConsumableInfo();
		pc->initConsumableInfo("猛烈一擊", "Scroll/Skillbook_01", SCROLL, false, 1, 1, 5, 10, "可以學習猛烈一擊技能", EDIBLE_SKILL, 1);
      addInfo(pc);
	}*/
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
            notifyItemUpdate();
				return true ;
			}else
			{
				//堆滿了
				st = m_iStack+st-pinfo->getStackLimit() ;
				m_iStack = pinfo->getStackLimit() ;
            notifyItemUpdate();
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
   else {
      m_iStack = 0;
      clear();
   }
}

void CItem::taken()
{
	m_iStack--;
	if(m_iStack <= 0)
	{
		clear();
	}

   notifyItemUpdate();
}

// Add by Darren Chen on 2013/01/21 {
void CItem::addItemEventListener(IItemEventListener *pListener)
{
   std::set<IItemEventListener *>::iterator it = m_itemEventListeners.find(pListener);
   if(it == m_itemEventListeners.end())
      m_itemEventListeners.insert(pListener);
}

void CItem::removeItemEventListener(IItemEventListener *pListener)
{
   std::set<IItemEventListener *>::iterator it = m_itemEventListeners.find(pListener);
   if(it != m_itemEventListeners.end())
      m_itemEventListeners.erase(it);
}

void CItem::notifyItemUpdate()
{
   std::set<IItemEventListener *>::iterator it = m_itemEventListeners.begin();
   while(it != m_itemEventListeners.end()) {
      (*it)->updateItemData(this);
      it++;
   }

   if(getID() == -1 && m_iStack == 0)
      m_itemEventListeners.clear();
}
// } Add by Darren Chen on 2013/01/21