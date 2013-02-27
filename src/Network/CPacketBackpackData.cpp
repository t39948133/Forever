#include "CPacketBackpackData.h"

long long CPacketBackpackData::getUID()
{
   return m_uid;
}

void CPacketBackpackData::pack(CPlayer *pPlayer)
{
   m_uid            = pPlayer->getUID();

   CBackpack *pBackpack = pPlayer->getBackpack();
   for(int i = 0; i < BACK_MAX; i++) {
      CItem *pItem = pBackpack->getItem(i);

      CNetDataBackpack netBackpack;
      netBackpack.m_grid   = i;
      netBackpack.m_itemID = pItem->getID();
      netBackpack.m_stack  = pItem->getStack();
      m_vBackpack[i] = netBackpack;
   }
}

void CPacketBackpackData::unpack(CPlayer *pPlayer)
{
   if(pPlayer->getUID() != m_uid)
      return;

   for(int i = 0; i < BACK_MAX; i++) {
      CItem newItem;
      newItem.create(m_vBackpack[i].m_itemID, m_vBackpack[i].m_stack);

      pPlayer->getBackpack()->setGrid(m_vBackpack[i].m_grid, newItem);
   }
}