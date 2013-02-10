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
/*#ifdef _GAMESERVER_
   // 藥水

   // 新手裝備
	m_itemBack[3].create(0, 1);
	m_itemBack[4].create(1, 1);
   m_itemBack[5].create(2, 1);

   // 武器
   m_itemBack[7].create(32, 1);
   m_itemBack[8].create(33, 1);
   m_itemBack[16].create(34, 1);
   m_itemBack[17].create(35, 1);
   m_itemBack[26].create(36, 1);

   // 技能書

   // 勇氣系列裝備
   m_itemBack[9].create(12, 1);
   m_itemBack[10].create(13, 1);
   m_itemBack[11].create(14, 1);
   m_itemBack[12].create(15, 1);
   m_itemBack[13].create(16, 1);
   m_itemBack[14].create(29, 1);

   // 守衛萬夫長系列裝備
   m_itemBack[18].create(17, 1);
   m_itemBack[19].create(18, 1);
   m_itemBack[20].create(19, 1);
   m_itemBack[21].create(20, 1);
   m_itemBack[22].create(21, 1);
   m_itemBack[23].create(30, 1);
#endif  // #ifdef _GAMESERVER_*/
}

void CBackpack::notifyPlayerBackpackUpdate()
{
   std::set<IPlayerBackpackEventListener *>::iterator it = m_playerBackpackEventListeners.begin();
   while(it != m_playerBackpackEventListeners.end()) {
      (*it)->updatePlayerBackpack(this);
      it++;
   }
}