#include "CPacketPlayerDataWG.h"

void CPacketPlayerDataWG::pack(long long netID, CPlayer *pPlayer)
{
   m_netID          = netID;
   m_uid            = pPlayer->getUID();
   m_level          = pPlayer->getLevel();
   m_strName        = pPlayer->getName();
   m_basAttr        = pPlayer->getBasAttr();
   m_advAttr        = pPlayer->getAdvAttr();
   m_position       = pPlayer->getPosition();
   m_targetPosition = pPlayer->getTargetPosition();
   m_fDirection     = pPlayer->getDirection();
   m_xp             = pPlayer->getXP();
   m_xpMax          = pPlayer->getXPMax();
   m_money          = pPlayer->getMoney();

   CBackpack *pBackpack = pPlayer->getBackpack();
   for(int i = 0; i < BACK_MAX; i++) {
      CItem *pItem = pBackpack->getItem(i);

      CNetDataBackpack netBackpack;
      netBackpack.m_grid   = i;
      netBackpack.m_itemID = pItem->getID();
      netBackpack.m_stack  = pItem->getStack();
      m_vBackpack[i] = netBackpack;
   }

   std::vector<CSkill *> vSkill = pPlayer->getSkill();
   if(vSkill.size() <= SKILL_MAX) {
      for(int i = 0; i < (int)vSkill.size(); i++) {
         CNetDataSkill netSkill;
         netSkill.m_skillID = vSkill.at(i)->getID();
         m_vSkill[i] = netSkill;
      }
   }

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

   for(int i = 0; i < pPlayer->getHotKeySize(); i++) {
      HotKeyItem *pHotKeyItem = pPlayer->getHotKeyItem(i);

      CNetDataHotKey netHotKey;
      netHotKey.m_field = pHotKeyItem->iField;
      netHotKey.m_backpackGrid = pHotKeyItem->iBackpackGrid;

      if(pHotKeyItem->pItem != NULL)
         netHotKey.m_itemID = pHotKeyItem->pItem->getID();
      else
         netHotKey.m_itemID = -1;

      if(pHotKeyItem->pSkill != NULL)
         netHotKey.m_skillID = pHotKeyItem->pSkill->getID();
      else
         netHotKey.m_skillID = -1;

      m_vHotKey[i] = netHotKey;
   }
}

void CPacketPlayerDataWG::unpack(CPlayer *pPlayer)
{
   pPlayer->setUID(m_uid);
   pPlayer->m_level   = m_level;
   pPlayer->m_strName = m_strName;
   pPlayer->setBasAttr(m_basAttr);
   pPlayer->setAdvAttr(m_advAttr);
   pPlayer->setPosition(m_position.fX, m_position.fY);
   pPlayer->setTargetPosition(m_targetPosition.fX, m_targetPosition.fY);
   pPlayer->setDirection(m_fDirection);
   pPlayer->m_xp      = m_xp;
   pPlayer->m_xpMax   = m_xpMax;
   pPlayer->addMoney(m_money);

   for(int i = 0; i < BACK_MAX; i++) {
      if(m_vBackpack[i].m_itemID != -1) {
         CItem newItem;
         newItem.create(m_vBackpack[i].m_itemID, m_vBackpack[i].m_stack);

         pPlayer->getBackpack()->setGrid(m_vBackpack[i].m_grid, newItem);
      }
   }

   for(int i = 0; i < SKILL_MAX; i++) {
      if(m_vSkill[i].m_skillID != -1)
         pPlayer->addSkill(m_vSkill[i].m_skillID);
   }

   for(int slot = MAIN_HAND; slot < MAX_SLOT; slot++) {
      if(m_mEquip[slot].m_itemID != -1)
         pPlayer->wearToEquipSlot(m_mEquip[slot].m_slot, m_mEquip[slot].m_itemID);
   }

   for(int i = 0; i < UI_HOTKEY_NUM; i++) {
      HotKeyItem newHotKeyItem;
      newHotKeyItem.iField = m_vHotKey[i].m_field;
      newHotKeyItem.iBackpackGrid = m_vHotKey[i].m_backpackGrid;

      if(m_vHotKey[i].m_itemID > -1) {
         for(int j = 0; j < pPlayer->getBackpack()->getSize(); j++) {
            CItem *pItem = pPlayer->getBackpack()->getItem(j);
            if(pItem->getID() == m_vHotKey[i].m_itemID) {
               newHotKeyItem.pItem = pItem;
               break;
            }
         }
      }
      else
         newHotKeyItem.pItem = NULL;

      if(m_vHotKey[i].m_skillID > -1) {
         for(int j = 0; j < (int)pPlayer->m_vSkill.size(); j++) {
            CSkill *pSkill = pPlayer->m_vSkill.at(j);
            if(pSkill->getID() == m_vHotKey[i].m_skillID) {
               newHotKeyItem.pSkill = pSkill;
               break;
            }
         }
      }
      else
         newHotKeyItem.pSkill = NULL;

      pPlayer->addHotKeyItem(newHotKeyItem);
   }
}