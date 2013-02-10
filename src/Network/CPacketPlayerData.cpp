#include "CPacketPlayerData.h"

long long CPacketPlayerData::getUID()
{
   return m_uid;
}

void CPacketPlayerData::pack(CPlayer *pPlayer)
{
   m_uid            = pPlayer->getUID();
   m_level          = pPlayer->getLevel();
   m_strName        = pPlayer->getName();
   m_basAttr        = pPlayer->getBasAttr();
   m_advAttr        = pPlayer->getAdvAttr();
   m_position       = pPlayer->getPosition();
   m_targetPosition = pPlayer->getTargetPosition();
   m_fDirection     = pPlayer->getDirection();

   std::map<EquipSlot, int> mEquip = pPlayer->getEquip();
   for(int slot = MAIN_HAND; slot < MAX_SLOT; slot++) {
      std::map<EquipSlot, int>::iterator it = mEquip.find((EquipSlot)slot);
      if(it != mEquip.end()) {
         CNetDataEquip netDataEquip;
         netDataEquip.m_slot = (*it).first;
         netDataEquip.m_itemID = (*it).second;
         m_mEquip[slot] = netDataEquip;
      }
   }
}

void CPacketPlayerData::unpack(CPlayer *pPlayer)
{
   pPlayer->setUID(m_uid);
   pPlayer->m_level   = m_level;
   pPlayer->m_strName = m_strName;
   pPlayer->setBasAttr(m_basAttr);
   pPlayer->setAdvAttr(m_advAttr);
   pPlayer->setPosition(m_position.fX, m_position.fY);
   pPlayer->setTargetPosition(m_targetPosition.fX, m_targetPosition.fY);
   pPlayer->setDirection(m_fDirection);

   for(int slot = MAIN_HAND; slot < MAX_SLOT; slot++) {
      if(m_mEquip[slot].m_itemID != -1)
         pPlayer->wearToEquipSlot(m_mEquip[slot].m_slot, m_mEquip[slot].m_itemID);
   }
}

#ifdef _GAMEENGINE_3D_
void CPacketPlayerData::unpack(CPlayer3D *pPlayer3D)
{
   this->unpack(pPlayer3D->getPlayer2D());

   //砞﹚家竚
   //pPlayer3D->setPosition(m_position.fX, 0, m_position.fY);

   //砞﹚家よ
   //pPlayer3D->setDirection(m_fDirection);

   //砞﹚家ぐ或杆称┪猌竟
   for(int slot = MAIN_HAND; slot < MAX_SLOT; slot++)
      pPlayer3D->updatePlayerEquip(pPlayer3D->getPlayer2D(), m_mEquip[slot].m_slot, m_mEquip[slot].m_itemID);
}
#endif