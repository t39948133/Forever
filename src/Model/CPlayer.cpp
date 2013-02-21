#include "CPlayer.h"
#include "CItem.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"
#include "AttributeSet.h"
#include "CMonster.h"

CPlayer::CPlayer(std::string machineName, std::string strName, long long uid, char level) : CUnitObject(machineName, strName, uid, level), 
                                                                                            m_levelMax(50)
{
   m_pBackpack = new CBackpack();
   m_pQuestMap = new CQuestMap();
   m_xp = 0;
   m_xpMax = level * 1000;
   m_money = 0;

   m_pvtHotKey = new std::vector<HotKeyItem *>();
   for(int i = 0; i < UI_HOTKEY_NUM; i++) {
      HotKeyItem *pHotKeyItem = new HotKeyItem();
      pHotKeyItem->iField = i;
      pHotKeyItem->pItem = NULL;
      pHotKeyItem->pSkill = NULL;
      m_pvtHotKey->push_back(pHotKeyItem);
   }

   // 讀取玩家動作檔 (守護星 的動作系統)
   if(m_actionSystem.read("../PlayerKnight.acs") == false)
      m_actionSystem.read("PlayerKnight.acs");
}

// Add by Darren Chen on 2013/01/12 {
CPlayer::~CPlayer()
{
   if(m_pvtHotKey != NULL) {
      std::vector<HotKeyItem *>::iterator it = m_pvtHotKey->begin();
      while(it != m_pvtHotKey->end()) {
         delete (*it);
         it++;
      }
      m_pvtHotKey->clear();
      delete m_pvtHotKey;
      m_pvtHotKey = NULL;
   }

   if(m_pBackpack != NULL) {
      delete m_pBackpack;
      m_pBackpack = NULL;
   }
}
// } Add by Darren Chen on 2013/01/12

void CPlayer::addXP(unsigned int xp)
{
	m_xp += xp;
	if(m_xpMax < m_xp)	//取得經驗後 可升級
	{		
		m_xp -= m_xpMax;
		//升級function
	}
   notifyPlayerAttrUpdate();
}

unsigned int CPlayer::getXP()
{
	return m_xp;
}

unsigned int CPlayer::getXPMax()
{
	return m_xpMax;
}

CBackpack* CPlayer::getBackpack()
{
	return m_pBackpack;
}

CQuestMap* CPlayer::getQuestMap()
{
	return m_pQuestMap;
}

// Modify by Darren Chen on 2013/01/07 {
void CPlayer::wearToEquipSlot(EquipSlot es, int itemID)
{
   std::string machineName = this->getMachineName();
   size_t idx = machineName.find("Server");
   if(idx != std::string::npos) {
      // Server端處理

      std::map<EquipSlot, int>::iterator it = m_mEquip.find(es);
      if(it != m_mEquip.end()) {
         // 舊物品放入背包
		   int st = 1;
		   int bu = 0;
		   m_pBackpack->addItem(it->second, st, bu);

         // 該裝備槽的資料移除
         m_mEquip.erase(it);
      }

	   // 物品裝備到裝備欄上
	   m_mEquip.insert(std::make_pair(es, itemID));
      notifyPlayerEquipUpdate(es, itemID);
   	
      // 背包的物品堆疊減一
      m_pBackpack->removeItem(itemID);
   }
   else {
      // Client端處理

      std::map<EquipSlot, int>::iterator it = m_mEquip.find(es);
      if(it != m_mEquip.end())
         // 該裝備槽的資料移除
         m_mEquip.erase(it);

	   // 物品裝備到裝備欄上
	   m_mEquip.insert(std::make_pair(es, itemID));
      notifyPlayerEquipUpdate(es, itemID);
   }

   updateEquipAttr();
}
// } Modify by Darren Chen on 2013/01/07

void CPlayer::shedEquip(EquipSlot grid)
{
   std::string machineName = this->getMachineName();
   size_t idx = machineName.find("Server");
   if(idx != std::string::npos) {
      // Server端處理

      std::map<EquipSlot, int>::iterator it = m_mEquip.find(grid);
	   if(m_mEquip.end() == it)
		   return;
   	
	   int st = 1;
	   int gr = 0;
	   m_pBackpack->addItem(it->second, st, gr);

	   m_mEquip.erase(grid);
      notifyPlayerEquipUpdate(grid, -1);
   }
   else {
      // Client端處理

      std::map<EquipSlot, int>::iterator it = m_mEquip.find(grid);
	   if(m_mEquip.end() == it)
		   return;

      m_mEquip.erase(grid);
      notifyPlayerEquipUpdate(grid, -1);
   }

   updateEquipAttr();
}

std::map<EquipSlot, int> CPlayer::getEquip()
{
	return m_mEquip;
}

int CPlayer::getEquip(EquipSlot equip)
{
	int id ;
   std::map<EquipSlot, int>::iterator it = m_mEquip.find(equip);
	if(m_mEquip.end() == it)
	{
		id = -1;
	}
	else
	{
		id = it->second;
	}
	return id;
}

// Add by Darren Chen on 2012/12/26 {
void CPlayer::addMoney(long long money)
{
   m_money += money;
   notifyPlayerAttrUpdate();
}

long long CPlayer::getMoney()
{
   return m_money;
}

void CPlayer::useItem(int itemID)
{
   std::string machineName = this->getMachineName();
   size_t idx = machineName.find("Server");
   if(idx != std::string::npos) {
      // Server端處理

      CItemInfo* pItemInfo = CItem::getInfo(itemID);
      if(pItemInfo == NULL)
         return;

      if(pItemInfo->getClassType() == WEAPON) {
		   CWeaponInfo *pWp = (CWeaponInfo*) pItemInfo;
         if(this->getLevel() >= pWp->getLevel()) {
            if(ONE_HAND == pWp->getWield())
			      wearToEquipSlot(MAIN_HAND, itemID);
            else if(TWO_HAND == pWp->getWield())
			      wearToEquipSlot(OFF_HAND, itemID);
         }
	   }
      else if(pItemInfo->getClassType() == ARMOR) {
		   CArmorInfo *pAm = (CArmorInfo*) pItemInfo;
         if(this->getLevel() >= pAm->getLevel()) {
		      if(CLOTHES == pAm->getWear())
			      wearToEquipSlot(CHEST, itemID);
		      else if(BELTS == pAm->getWear())
			      wearToEquipSlot(BELT, itemID);
		      else if(PANTS == pAm->getWear())
			      wearToEquipSlot(LEGS, itemID);
		      else if(PAULDRONS == pAm->getWear())
			      wearToEquipSlot(SHOULDER, itemID);
		      else if(GLOVES == pAm->getWear())
			      wearToEquipSlot(GLOVE, itemID);
		      else if(BOOTS == pAm->getWear())
			      wearToEquipSlot(BOOT, itemID);
         }
	   }
      else if(pItemInfo->getClassType() == CONSUMABLE) {
         CConsumableInfo *pConsumableInfo = (CConsumableInfo *)pItemInfo;
         if(this->getLevel() >= pConsumableInfo->getLevel()) {
            if(pConsumableInfo->getEffect() == EDIBLE_SKILL)
               addSkill(pConsumableInfo->getMuch());  // 學習某項技能   
            else if(pConsumableInfo->getEffect() == EDIBLE_HP) {
               if(getHPMax() == getHP())
                    return;

               addHP(pConsumableInfo->getMuch());     // 補血
               // Todo: 藥水是否有CD時間
            }
            else if(pConsumableInfo->getEffect() == EDIBLE_MP) {
               if(getMP() == getMPMax())
                  return;

               addMP(pConsumableInfo->getMuch());     // 補魔
               // Todo: 藥水是否有CD時間
            }
            else
               return;

            // 背包物品減一
            m_pBackpack->removeItem(itemID);
         }
      }
   }
   else {
      // Client端處理
   }
}

void CPlayer::addHotKeyItem(HotKeyItem &newHotKeyItem)
{
   if(newHotKeyItem.iField >= 0 && newHotKeyItem.iField < (int)m_pvtHotKey->size()) {
      HotKeyItem *pHotKeyItem = m_pvtHotKey->at(newHotKeyItem.iField);
      if(pHotKeyItem != NULL) {
         if(newHotKeyItem.pItem != NULL) {
            if(newHotKeyItem.iBackpackGrid > -1) {
               CItem *pBackpackItem = m_pBackpack->getItem(newHotKeyItem.iBackpackGrid);
               if(pBackpackItem != NULL) {
                  if(newHotKeyItem.pItem->getID() == pBackpackItem->getID()) {
                     pHotKeyItem->iField = newHotKeyItem.iField;
                     pHotKeyItem->pItem = pBackpackItem;
                     pHotKeyItem->iBackpackGrid = newHotKeyItem.iBackpackGrid;
                     pHotKeyItem->pSkill = NULL;
                  }
               }
            }
         }
         else if(newHotKeyItem.pSkill != NULL) {
            std::vector<CSkill *>::iterator it = m_vSkill.begin();
            while(it != m_vSkill.end()) {
               if(newHotKeyItem.pSkill->getID() == (*it)->getID()) {
                  pHotKeyItem->iField = newHotKeyItem.iField;
                  pHotKeyItem->pSkill = (*it);
                  pHotKeyItem->pItem = NULL;
                  pHotKeyItem->iBackpackGrid = -1;

                  break;
               }
               it++;
            }
         }
         else {
            pHotKeyItem->iField = newHotKeyItem.iField;
            pHotKeyItem->pItem = NULL;
            pHotKeyItem->iBackpackGrid = -1;
            pHotKeyItem->pSkill = NULL;
         }

         notifyPlayerHotKeyUpdate(pHotKeyItem);

         if(pHotKeyItem->pSkill != NULL)
            pHotKeyItem->pSkill->checkAvailable(m_mEquip);
      }
   }
}

HotKeyItem* CPlayer::getHotKeyItem(int field)
{
   if(field >= 0 && (size_t)field < m_pvtHotKey->size()) {
      return m_pvtHotKey->at(field);
   }
   else
      return NULL;
}

int CPlayer::getHotKeySize()
{
   return (int)m_pvtHotKey->size();
}

void CPlayer::skillDamage(AdvancedAttribute targetAttr)
{
    CMonster *pTargetMonster = dynamic_cast<CMonster *>(getTargetObject());
    if(pTargetMonster != NULL)
    {
		  AdvancedAttribute monsterAdv = pTargetMonster->getAdvAttr();
        pTargetMonster->addHate(getUID(), targetAttr.iHP - monsterAdv.iHP);
    }
    CUnitObject::skillDamage(targetAttr);
}

void CPlayer::addPlayerAttrEventListener(IPlayerAttrEventListener *pListener)
{
   std::set<IPlayerAttrEventListener *>::iterator it = m_playerAttrEventListeners.find(pListener);
   if(it == m_playerAttrEventListeners.end())
      m_playerAttrEventListeners.insert(pListener);
}

void CPlayer::removePlayerAttrEventListener(IPlayerAttrEventListener *pListener)
{
   std::set<IPlayerAttrEventListener *>::iterator it = m_playerAttrEventListeners.find(pListener);
   if(it != m_playerAttrEventListeners.end())
      m_playerAttrEventListeners.erase(it);
}

void CPlayer::addPlayerEquipEventListener(IPlayerEquipEventListener *pListener)
{
   std::set<IPlayerEquipEventListener *>::iterator it = m_playerEquipEventListeners.find(pListener);
   if(it == m_playerEquipEventListeners.end())
      m_playerEquipEventListeners.insert(pListener);
}

void CPlayer::removePlayerEquipEventListener(IPlayerEquipEventListener *pListener)
{
   std::set<IPlayerEquipEventListener *>::iterator it = m_playerEquipEventListeners.find(pListener);
   if(it != m_playerEquipEventListeners.end())
      m_playerEquipEventListeners.erase(it);
}

void CPlayer::addPlayerBackpackEventListener(IPlayerBackpackEventListener *pListener)
{
   m_pBackpack->addPlayerBackpackEventListener(pListener);
}

void CPlayer::removePlayerBackpackEventListener(IPlayerBackpackEventListener *pListener)
{
   m_pBackpack->removePlayerBackpackEventListener(pListener);
}

void CPlayer::addPlayerHotKeyEventListener(IPlayerHotKeyEventListener *pListener)
{
   std::set<IPlayerHotKeyEventListener *>::iterator it = m_playerHotKeyEventListeners.find(pListener);
   if(it == m_playerHotKeyEventListeners.end())
      m_playerHotKeyEventListeners.insert(pListener);
}

void CPlayer::removePlayerHotKeyEventListener(IPlayerHotKeyEventListener *pListener)
{
   std::set<IPlayerHotKeyEventListener *>::iterator it = m_playerHotKeyEventListeners.find(pListener);
   if(it != m_playerHotKeyEventListeners.end())
      m_playerHotKeyEventListeners.erase(it);
}

#ifdef _GAMEENGINE_2D_
void CPlayer::draw(HDC hdc)
{
   CUnitObject::draw(hdc);

   int size = 20;
   char buf[128];
   sprintf_s(buf, sizeof(buf), "%s", getName().c_str());
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY + size + 5, buf, strlen(buf));

   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "目標位置: x = %.0f, y = %.0f", this->getTargetPosition().fX, this->getTargetPosition().fY);
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY - size * 2, buf, strlen(buf));
}
#endif  // #ifdef _GAMEENGINE_2D_
// } Add by Darren Chen on 2012/12/26

void CPlayer::updateEquipAttr()
{
   std::string machineName = this->getMachineName();
   size_t idx = machineName.find("Server");
   if(idx != std::string::npos) {
      // Server端處理

	   std::map<EquipSlot , int>::iterator pi = m_mEquip.begin();
	   AdvancedAttribute advAttr;
	   AttributeSet(advAttr);
	   ObscureAttribute obsAttr;
	   AttributeClear(obsAttr);
	   BasicAttributeSet(getLevel(), getBasAttr(), advAttr, obsAttr);		//取得角色初始素質
	   while (m_mEquip.end() != pi)
	   {
		   CWeaponInfo* wp = (CWeaponInfo*) CItem::getInfo(pi->second);
		   if(NULL == wp)
		   {
			   break;
		   }
		   AttributeAdd (advAttr, wp->getBaseAttr());
		   AttributeAdd (advAttr, wp->getExtendAttr());
   		
		   pi++;
	   }
	   advAttr.iHP = getHP();
	   advAttr.iMP = getMP();
	   setAdvAttr(advAttr);
	   updateSkillAvailable();
   }
   else {
      // Client端處理

      updateSkillAvailable();
   }
}

void CPlayer::updateSkillAvailable()
{
    std::vector<CSkill *>::iterator ps = m_vSkill.begin();
    while(m_vSkill.end() != ps)
    {
        (*ps)->checkAvailable(getEquip());
        ps++;
    }
}

// Add by Darren Chen on 2013/01/17 {
void CPlayer::notifyPlayerAttrUpdate()
{
   std::set<IPlayerAttrEventListener *>::iterator it = m_playerAttrEventListeners.begin();
   while(it != m_playerAttrEventListeners.end()) {
      (*it)->updatePlayerAttr(this);
      it++;
   }
}

void CPlayer::notifyPlayerEquipUpdate(EquipSlot es, int itemID)
{
   std::set<IPlayerEquipEventListener *>::iterator it = m_playerEquipEventListeners.begin();
   while(it != m_playerEquipEventListeners.end()) {
      (*it)->updatePlayerEquip(this, es, itemID);
      it++;
   }
}

void CPlayer::notifyPlayerHotKeyUpdate(HotKeyItem *pHotKeyItem)
{
   std::set<IPlayerHotKeyEventListener *>::iterator it = m_playerHotKeyEventListeners.begin();
   while(it != m_playerHotKeyEventListeners.end()) {
      (*it)->updatePlayerHotKey(pHotKeyItem);
      it++;
   }
}
// } Add by Darren Chen on 2013/01/17