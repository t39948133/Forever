#include "CPlayer.h"
#include "CItem.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"
#include "AttributeSet.h"
#include "CMonster.h"

CPlayer::CPlayer(std::string strName, long long uid, char level) : CUnitObject(strName, uid, level), m_levelMax(50)
{
   BasicAttribute basAttr;
   AttributeClear(basAttr);
   basAttr.iSTR = 115;
   basAttr.iVIT = 110;
   basAttr.iDEX = 100;
   basAttr.iAGI = 100;
   basAttr.iINT = 90;
   basAttr.iWIL = 105;
   setBasAttr(basAttr);
   m_backPack.initBack();
   updateEquipAttr();
   // Add by Darren Chen on 2013/01/05 {
   m_xp = 0;
   m_xpMax = 1000;
   m_money = 0;

   m_pvtHotKey = new std::vector<HotKeyItem *>();
   for(int i = 0; i < UI_HOTKEY_NUM; i++) {
      HotKeyItem *pHotKeyItem = new HotKeyItem();
      pHotKeyItem->pItem = NULL;
      pHotKeyItem->pSkill = NULL;
      m_pvtHotKey->push_back(pHotKeyItem);
   }

   // 讀取玩家動作檔
   m_pActionSystem->read("../player.acs");

   // 玩家擁有技能
   addSkill(0);
   // } Add by Darren Chen on 2013/01/05
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

CBackPack CPlayer::getBackPack()
{
	return m_backPack;
}

void CPlayer::shedEquip(EquipSlot grid)
{
   std::map<EquipSlot, int>::iterator it = m_mEquip.find(grid);
	if(m_mEquip.end() == it)
		return;
	
	int st = 1;
	int gr = 0;
	m_backPack.addItem(it->second, st, gr);
   notifyPlayerBackpackUpdate();

	m_mEquip.erase(grid);
   notifyPlayerEquipUpdate();

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

void CPlayer::useItem(unsigned int itemID)
{
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
         else
            return;

         updateEquipAttr();
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
         else
            return;

         updateEquipAttr();
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
         for(int i = 0; i < BACK_MAX; i++) {
            CItem *pFindItem = m_backPack.getItem(i);
            if(pFindItem->getInfo() == pItemInfo) {
               pFindItem->taken();

               notifyPlayerBackpackUpdate();
               break;
            }
         }
      }
   }
}

void CPlayer::addHotKeyItem(HotKeyItem &newHotKeyItem)
{
   if(newHotKeyItem.iField >= 0 && newHotKeyItem.iField < (int)m_pvtHotKey->size()) {
      HotKeyItem *pHotKeyItem = m_pvtHotKey->at(newHotKeyItem.iField);
      if(pHotKeyItem != NULL) {
         if(newHotKeyItem.pItem != NULL) {
            for(int i = 0; i < m_backPack.getSize(); i++) {
               CItem *pBackpackItem = m_backPack.getItem(i);
               if(pBackpackItem != NULL) {
                  if(newHotKeyItem.pItem->getID() == pBackpackItem->getID()) {
                     pHotKeyItem->iField = newHotKeyItem.iField;
                     pHotKeyItem->pItem = pBackpackItem;
                     pHotKeyItem->pSkill = NULL;
                     break;
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

                  (*it)->checkAvailable(m_mEquip);
                  break;
               }
               it++;
            }
         }
         else {
            pHotKeyItem->iField = newHotKeyItem.iField;
            pHotKeyItem->pItem = NULL;
            pHotKeyItem->pSkill = NULL;
         }

         notifyPlayerHotKeyUpdate(pHotKeyItem);
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
   std::set<IPlayerBackpackEventListener *>::iterator it = m_playerBackpackEventListeners.find(pListener);
   if(it == m_playerBackpackEventListeners.end())
      m_playerBackpackEventListeners.insert(pListener);
}

void CPlayer::removePlayerBackpackEventListener(IPlayerBackpackEventListener *pListener)
{
   std::set<IPlayerBackpackEventListener *>::iterator it = m_playerBackpackEventListeners.find(pListener);
   if(it != m_playerBackpackEventListeners.end())
      m_playerBackpackEventListeners.erase(it);
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
}
#endif  // #ifdef _GAMEENGINE_2D_
// } Add by Darren Chen on 2012/12/26

void CPlayer::updateEquipAttr()
{
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

void CPlayer::updateSkillAvailable()
{
    std::vector<CSkill *>::iterator ps = m_vSkill.begin();
    while(m_vSkill.end() != ps)
    {
        (*ps)->checkAvailable(getEquip());
        ps++;
    }
}

// Modify by Darren Chen on 2013/01/07 {
void CPlayer::wearToEquipSlot(EquipSlot es, unsigned int id)
{
   std::map<EquipSlot, int>::iterator it = m_mEquip.find(es);
	if(m_mEquip.end() == it)
	{
      // 背包的物品堆疊減一
      CItemInfo *pFindItemInfo = CItem::getInfo(id);
      for(int i = 0; i < BACK_MAX; i++) {
         CItem *pItem = m_backPack.getItem(i);
         if(pItem->getInfo() == pFindItemInfo) {
            pItem->taken();
            notifyPlayerBackpackUpdate();
            break;
         }
      }

      // 物品裝備到裝備欄上
		m_mEquip.insert(std::make_pair(es, id));
      notifyPlayerEquipUpdate();
	}
	else
	{
      // 舊物品放入背包
		int st = 1;
		int bu = 0;
		m_backPack.addItem(it->second, st, bu);
      notifyPlayerBackpackUpdate();

      // 新物品裝備到裝備欄上
		m_mEquip.insert(std::make_pair(es, id));
      notifyPlayerEquipUpdate();
	}
}
// } Modify by Darren Chen on 2013/01/07

// Add by Darren Chen on 2013/01/17 {
void CPlayer::notifyPlayerAttrUpdate()
{
   std::set<IPlayerAttrEventListener *>::iterator it = m_playerAttrEventListeners.begin();
   while(it != m_playerAttrEventListeners.end()) {
      (*it)->updatePlayerAttr(this);
      it++;
   }
}

void CPlayer::notifyPlayerEquipUpdate()
{
   std::set<IPlayerEquipEventListener *>::iterator it = m_playerEquipEventListeners.begin();
   while(it != m_playerEquipEventListeners.end()) {
      (*it)->updatePlayerEquip(this);
      it++;
   }
}

void CPlayer::notifyPlayerBackpackUpdate()
{
   std::set<IPlayerBackpackEventListener *>::iterator it = m_playerBackpackEventListeners.begin();
   while(it != m_playerBackpackEventListeners.end()) {
      (*it)->updatePlayerBackpack(this);
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