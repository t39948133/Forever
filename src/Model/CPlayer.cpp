#include "CPlayer.h"
#include "CItem.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"
#include "AttributeSet.h"

CPlayer::CPlayer(std::string strName, long long uid, char level) : CUnitObject(strName, uid, level), m_levelMax(50)
{
   m_backPack.initBack();
   updateEquipAttr();
   // Add by Darren Chen on 2013/01/05 {
   m_xp = 0;
   m_xpMax = 1000;
   m_money = 0;
   // } Add by Darren Chen on 2013/01/05

   // Add by Darren Chen on 2012/12/27 {
   ACTION_DATA actData;
   CActionEvent actEvent;
   CAction *pAction = NULL;
   CActionEventHandler *pActionEventHandler = NULL;

   // Idle動作->(座標更動)->跑步動作
   actData.iID           = 1;
   actData.name          = "等待";
   actData.fTime         = 4.33333f;
   actData.animationName = "lm_nidle_001";
   actData.iNextActID    = 0;  // 沒有下一個動作
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'W';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'A';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'S';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'D';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_NOT_REACH;
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY;
   actEvent.m_iKeyID     = 'X';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 3);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);

   // 跑步動作->(座標無更動)->Idle動作
   actData.iID           = 2;
   actData.name          = "跑步";
   actData.fTime         = 1.46667f;
   actData.animationName = "lm_nrun_001";
   actData.iNextActID    = 0;  // 沒有下一個動作
   actData.bMove         = true;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'W';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'A';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'S';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'D';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_REACH;
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);

   // Idle動作->(拔出武器快捷鍵)->戰鬥姿態動作
   actData.iID           = 3;
   actData.name          = "拔出武器";
   actData.fTime         = 1.33333f;
   actData.animationName = "lm_cdraw_2weapon_001";
   actData.iNextActID    = 4;  
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);
   m_pActionSystem->addAction(pAction);

   actData.iID           = 4;
   actData.name          = "戰鬥姿勢";
   actData.fTime         = 1.0f;
   actData.animationName = "lm_cidle_2weapon_001";
   actData.iNextActID    = 0;  // 沒有下一個動作
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event      = AET_KEY;
   actEvent.m_iKeyID     = 'X';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 5);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);

   actData.iID           = 5;
   actData.name          = "收回武器";
   actData.fTime         = 1.66667f;
   actData.animationName = "lm_nputin_2weapon_001";
   actData.iNextActID    = 1;  
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);
   m_pActionSystem->addAction(pAction);
   // } Add by Darren Chen on 2012/12/27
}

void CPlayer::addXP(unsigned int xp)
{
	m_xp += xp;
	if(m_xpMax < m_xp)	//取得經驗後 可升級
	{		
		m_xp -= m_xpMax;
		//升級function
	}
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
	m_mEquip.erase(grid);
	updateEquipAttr();
}

void CPlayer::updateEquipAttr()
{
	std::map<EquipSlot , int>::iterator pi = m_mEquip.begin();
	AdvancedAttribute advAttr;
	AttributeSet(advAttr);
	ObscureAttribute obsAttr;
	AttributeClear(obsAttr);
	BasisAttributeSet(getLevel(), getBasAttr(), advAttr, obsAttr);		//取得角色初始素質
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
    std::vector<CSkill>::iterator ps = m_vSkill.begin();
    while(m_vSkill.end() != ps)
    {
        ps->chackAvailable(getEquip());
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
            break;
         }
      }

      // 物品裝備到裝備欄上
		m_mEquip.insert(std::make_pair(es, id));
	}
	else
	{
      // 舊物品放入背包
		int st = 1;
		int bu = 0;
		m_backPack.addItem(it->second, st, bu);

      // 新物品裝備到裝備欄上
		m_mEquip.insert(std::make_pair(es, id));
	}
}
// } Modify by Darren Chen on 2013/01/07

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
}

long long CPlayer::getMoney()
{
   return m_money;
}

void CPlayer::useItem(unsigned int id)
{
   CItemInfo* pItemInfo = CItem::getInfo(id);
   if(pItemInfo == NULL)
      return;

   if(pItemInfo->getClassType() == WEAPON) {
		CWeaponInfo *pWp = (CWeaponInfo*) pItemInfo;
      if(this->getLevel() >= pWp->getLevel()) {
         if(ONE_HAND == pWp->getWield())
			   wearToEquipSlot(MAIN_HAND, id);
         else if(TWO_HAND == pWp->getWield())
			   wearToEquipSlot(OFF_HAND, id);
         else
            return;

         updateEquipAttr();
      }
	}
   else if(pItemInfo->getClassType() == ARMOR) {
		CArmorInfo *pAm = (CArmorInfo*) pItemInfo;
      if(this->getLevel() >= pAm->getLevel()) {
		   if(CLOTHES == pAm->getWear())
			   wearToEquipSlot(CHEST, id);
		   else if(BELTS == pAm->getWear())
			   wearToEquipSlot(BELT, id);
		   else if(PANTS == pAm->getWear())
			   wearToEquipSlot(LEGS, id);
		   else if(PAULDRONS == pAm->getWear())
			   wearToEquipSlot(SHOULDER, id);
		   else if(GLOVES == pAm->getWear())
			   wearToEquipSlot(GLOVE, id);
		   else if(BOOTS == pAm->getWear())
			   wearToEquipSlot(BOOT, id);
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
         else if(pConsumableInfo->getEffect() == EDIBLE_HP)
         {
             if(getHPMax() == getHP())
             {
                 return;
             }
            addHP(pConsumableInfo->getMuch());     // 補血
            // Todo: 藥水是否有CD時間
         }
         else
            return;

         // 背包物品減一
         for(int i = 0; i < BACK_MAX; i++) {
            CItem *pFindItem = m_backPack.getItem(i);
            if(pFindItem->getInfo() == pItemInfo) {
               pFindItem->taken();
               break;
            }
         }
      }
   }
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