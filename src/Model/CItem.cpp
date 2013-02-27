#include "CItem.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"
#include "AttributeSet.h"

void CItem::initItem ()
{
   if(ITEM_INFO::read("../Item.fla") == false)
      ITEM_INFO::read("Item.fla");
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

   notifyItemUpdate();
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