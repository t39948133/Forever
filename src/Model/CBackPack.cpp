#include "CBackpack.h"

void CBackpack::setGrid(int grid, CItem& itm)
{
   if((grid >= 0) && (grid < BACK_MAX)) {
      m_itemBack[grid].create(itm.getID(), itm.getStack());
      notifyPlayerBackpackUpdate();
   }
}

CItem* CBackpack::getItem(int grid)
{
	if((grid >= 0) && (grid < BACK_MAX))
	{
		return &(m_itemBack[grid]);
	}
	else
	{
		return NULL;
	}
}

CItemInfo* CBackpack::getItemInfo(int grid)
{
    CItem* pc = getItem(grid);					
    if (pc != NULL)
        return pc->getInfo () ;
    return NULL ;
}

void CBackpack::addItem(int itemID, int &stack, int &grid)
{
	for(int i = 0; i < BACK_MAX; i++)
	{
		m_itemBack[i].addStack(itemID, stack);
		if(stack == 0)
		{
			grid = i;
         notifyPlayerBackpackUpdate();
			break;
		}
	}
}

void CBackpack::removeItem(int itemID)
{
   CItemInfo *pFindItemInfo = CItem::getInfo(itemID);

   for(int i = 0; i < BACK_MAX; i++) {
      CItem *pItem = getItem(i);
      if(pItem->getInfo() == pFindItemInfo) {
         pItem->taken();
         notifyPlayerBackpackUpdate();
         break;
      }
   }
}

void CBackpack::removeGrid(int grid)
{
	CItem *pItem = getItem(grid);
	pItem->clear();
}

// Add by Darren Chen on 2013/01/13 {
int CBackpack::getSize()
{
   return BACK_MAX;
}

void CBackpack::addPlayerBackpackEventListener(IPlayerBackpackEventListener *pListener)
{
   std::set<IPlayerBackpackEventListener *>::iterator it = m_playerBackpackEventListeners.find(pListener);
   if(it == m_playerBackpackEventListeners.end())
      m_playerBackpackEventListeners.insert(pListener);
}

void CBackpack::removePlayerBackpackEventListener(IPlayerBackpackEventListener *pListener)
{
   std::set<IPlayerBackpackEventListener *>::iterator it = m_playerBackpackEventListeners.find(pListener);
   if(it != m_playerBackpackEventListeners.end())
      m_playerBackpackEventListeners.erase(it);
}
// } Add by Darren Chen on 2013/01/13

void CBackpack::initBack()
{
}

bool CBackpack::isFull()
{
	for(int i = 0; i < BACK_MAX; i++)
	{
		if(m_itemBack[i].getInfo() == NULL)
		{
			return false;
		}
	}
	return true;	
}

void CBackpack::notifyPlayerBackpackUpdate()
{
   std::set<IPlayerBackpackEventListener *>::iterator it = m_playerBackpackEventListeners.begin();
   while(it != m_playerBackpackEventListeners.end()) {
      (*it)->updatePlayerBackpack(this);
      it++;
   }
}