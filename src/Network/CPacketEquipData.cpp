#include "CPacketEquipData.h"

long long CPacketEquipData::getUID()
{
   return m_uid;
}

void CPacketEquipData::pack(CPlayer *pPlayer, EquipSlot equipSlot, int itemId)
{
   m_uid             = pPlayer->getUID();

   m_mEquip.m_slot   = equipSlot;
   m_mEquip.m_itemID = itemId;
}

void CPacketEquipData::unpack(CPlayer *pPlayer)
{
   if(pPlayer->getUID() != m_uid)
      return;

   if(m_mEquip.m_itemID != -1)
      pPlayer->wearToEquipSlot(m_mEquip.m_slot, m_mEquip.m_itemID);
   else
      pPlayer->shedEquip(m_mEquip.m_slot);
}

#ifdef _GAMEENGINE_3D_
void CPacketEquipData::unpack(CPlayer3D *pPlayer3D)
{
   this->unpack(pPlayer3D->getPlayer2D());

   //設定模型穿什麼裝備或武器
   pPlayer3D->updatePlayerEquip(pPlayer3D->getPlayer2D(), m_mEquip.m_slot, m_mEquip.m_itemID);
}
#endif