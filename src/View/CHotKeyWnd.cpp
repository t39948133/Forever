#include "CHotKeyWnd.h"
#include "CSkill.h"
#include "CItem.h"
#include "CPacketUseItem.h"
#include "CPacketCanUseSkill.h"

CHotKeyWnd::CHotKeyWnd()
{
#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;
#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
#endif
}

CHotKeyWnd::~CHotKeyWnd()
{
   if(m_pPlayer != NULL) {
      m_pPlayer->removePlayerHotKeyEventListener(this);
      m_pPlayer->removeAdvAttrEventListener(this);
   }

#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }
   }
#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }
   }

   for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_vpText[i] != NULL) {
         delete m_vpText[i];
         m_vpText[i] = NULL;
      }
   }
#endif
}

#ifdef _GAMEENGINE_3D_
void CHotKeyWnd::init(int _x, int _y, CPlayer *pPlr, int zOrder, GP::NetStream *pNetStream)
#elif _GAMEENGINE_2D_
void CHotKeyWnd::init(int _x, int _y, CPlayer *pPlr, GP::NetStream *pNetStream)
#endif
{
   m_pPlayer = pPlr;
   m_pNetStream = pNetStream;
   if(m_pPlayer != NULL) {
      m_pPlayer->addPlayerHotKeyEventListener(this);
      m_pPlayer->addAdvAttrEventListener(this);
   }

   x = _x;
	y = _y;

#ifdef _GAMEENGINE_3D_
   w = 431;
   h = 44;
#elif _GAMEENGINE_2D_
	w = BUTTON_COUNT*CELL_SIZE;
	h = CELL_SIZE;
#endif

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
   m_overlay.setZOrder(zOrder);

	//熱鍵
	for(int i = 0; i < BUTTON_COUNT; i++) {
		m_vpBtn[i] = new CHotKeyButton();
		m_vpBtn[i]->init(&m_overlay, 2 + i * ICON_SIZE + 3 * i, 2, ICON_SIZE, ICON_SIZE, i);
      m_vpBtn[i]->setImage("UI/Icon/NullBackpack");
      m_vpBtn[i]->setTextVisible(true);
      m_vpBtn[i]->setTextHorizontalAlignment(CImageButton::H_RIGHT);
      m_vpBtn[i]->setTextVerticalAlignment(CImageButton::V_BOTTOM);
      m_vpBtn[i]->setText("", 1, 1, 1);

      char buf[5];
      memset(buf, 0, sizeof(buf));
      if(i == 9)
         sprintf_s(buf, sizeof(buf), "0");
      else
         sprintf_s(buf, sizeof(buf), "%d", i + 1);
      m_vpBtn[i]->setHotKeyText(buf, 1, 1, 1);
      m_bvCoolDown[i] = false;
		addChild(m_vpBtn[i]);
	}
#else _GAMEENGINE_2D_
	//熱鍵內容(食物或技能)
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		m_vpBtn[i] = new CTextButton();
		m_vpBtn[i]->init (i*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;
		addChild (m_vpBtn[i]) ;
	}

	//相對應熱鍵值
	for (int i = 0; i<TEXT_COUNT/2; i++)
	{
		m_vpText[i] = new CTextArea();
		m_vpText[i]->init (i*CELL_SIZE, -18, CELL_SIZE/2, CELL_SIZE/2) ;
		char buf[256] ;
		if (i == TEXT_COUNT/2-1)
		{
			m_vpText[i]->setText ("0", 1, 1, 0) ;
		}else
		{
			sprintf_s (buf, sizeof (buf), "%d", i+1) ;
			m_vpText[i]->setText (buf, 1, 1, 0) ;
		}
		
		addChild (m_vpText[i]) ;
	}

	//堆疊數量
	for (int i = TEXT_COUNT/2; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextArea();
		m_vpText[i]->init ((i-TEXT_COUNT/2)*CELL_SIZE+20, 20, CELL_SIZE/2, CELL_SIZE/2) ;		
		addChild (m_vpText[i]) ;
	}
#endif

   show(true);
}

bool CHotKeyWnd::canDrag(int tx, int ty)
{
	return false;
}

void CHotKeyWnd::onLCommand(int btnID)
{
   // 使用物品或技能
   if(btnID >= 0 && btnID < m_pPlayer->getHotKeySize()) {
      HotKeyItem *pHotKeyItem = m_pPlayer->getHotKeyItem(btnID);
      if(pHotKeyItem->pItem != NULL) {
         CItemInfo *pItemInfo = pHotKeyItem->pItem->getInfo();
         if(pItemInfo != NULL) {
            CPacketUseItem packet;
            packet.pack(m_pPlayer, pHotKeyItem->iBackpackGrid, pHotKeyItem->pItem);
            m_pNetStream->send(&packet, sizeof(packet));
         }
      }
      else if(pHotKeyItem->pSkill != NULL) {
         if(m_pPlayer->canUseSkill(pHotKeyItem->pSkill->getID()) == true) {
            CPacketCanUseSkill packet;
            packet.pack(m_pPlayer, pHotKeyItem->pSkill->getID());
            m_pNetStream->send(&packet, sizeof(packet));
         }
      }
   }
}

void CHotKeyWnd::onRCommand(int btnID)
{
   // 移除HotKey上的物品或技能
   if(btnID >= 0 && btnID < m_pPlayer->getHotKeySize()) {
      HotKeyItem *pOldHotKeyItem = m_pPlayer->getHotKeyItem(btnID);
      if(pOldHotKeyItem->pSkill != NULL) {
         pOldHotKeyItem->pSkill->removeSkillEventListener(this);

         std::map<void *, int>::iterator it = m_table.find(pOldHotKeyItem->pSkill);
         if(it != m_table.end())
            m_table.erase(it);
      }
      else if(pOldHotKeyItem->pItem != NULL) {
         pOldHotKeyItem->pItem->removeItemEventListener(this);

         std::map<void *, int>::iterator it = m_table.find(pOldHotKeyItem->pItem);
         if(it != m_table.end())
            m_table.erase(it);
      }

      HotKeyItem newHotKeyItem;
      newHotKeyItem.iField = btnID;
      newHotKeyItem.pSkill = NULL;
      newHotKeyItem.pItem = NULL;
      newHotKeyItem.iBackpackGrid = -1;
      m_pPlayer->addHotKeyItem(newHotKeyItem);
   }
}

WindowClassType CHotKeyWnd::getClassType()
{
   return WND_HOTKEY;
}

void CHotKeyWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

void CHotKeyWnd::updatePlayerHotKey(HotKeyItem *pHotKeyItem)
{
   if(pHotKeyItem->pSkill != NULL) {
      pHotKeyItem->pSkill->addSkillEventListener(this);
      CSkillInfo *pSkillInfo = pHotKeyItem->pSkill->getInfo();

      if(pSkillInfo != NULL) {
#ifdef _GAMEENGINE_3D_
         m_vpBtn[pHotKeyItem->iField]->setImage(pSkillInfo->geticonName());
#elif _GAMEENGINE_2D_
         m_vpBtn[pHotKeyItem->iField]->str = pSkillInfo->getName();
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

         m_table.insert(std::pair<void *, int>(pHotKeyItem->pSkill, pHotKeyItem->iField));
      }
   }
   else if(pHotKeyItem->pItem != NULL) {
      if(pHotKeyItem->pItem->getStack() > 0) {
         pHotKeyItem->pItem->addItemEventListener(this);
         CItemInfo *pItemInfo = pHotKeyItem->pItem->getInfo();

         if(pItemInfo != NULL) {
#ifdef _GAMEENGINE_3D_
            m_vpBtn[pHotKeyItem->iField]->setImage(pItemInfo->geticonName());
            
            //堆疊數量
            char buf[10];
			   sprintf_s(buf, sizeof (buf), "%d", pHotKeyItem->pItem->getStack());
            m_vpBtn[pHotKeyItem->iField]->setText(buf, 1, 1, 1);
#elif _GAMEENGINE_2D_
            m_vpBtn[pHotKeyItem->iField]->str = pItemInfo->getName();

            //堆疊數量
            char buf[10];
			   sprintf_s(buf, sizeof (buf), "%d", pHotKeyItem->pItem->getStack());
			   m_vpText[TEXT_COUNT/2 + pHotKeyItem->iField]->setText (buf, 1, 1, 1) ;
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

            m_table.insert(std::pair<void *, int>(pHotKeyItem->pItem, pHotKeyItem->iField));
         }
      }
   }
   else {
#ifdef _GAMEENGINE_3D_
         m_vpBtn[pHotKeyItem->iField]->setImage("UI/Icon/NullBackpack");
         m_vpBtn[pHotKeyItem->iField]->setText("", 1, 1, 1);
#elif _GAMEENGINE_2D_
         m_vpBtn[pHotKeyItem->iField]->str = "";
         m_vpText[TEXT_COUNT/2 + pHotKeyItem->iField]->setText("", 1, 1, 1);
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
   }
}

void CHotKeyWnd::updateItemData(CItem *pItem)
{
   if(pItem != NULL) {
      std::map<void *, int>::iterator it = m_table.find(pItem);
      if(it != m_table.end()) {
         int field = it->second;

         if(pItem->getStack() > 0) {
            CItemInfo *pItemInfo = pItem->getInfo();

            if(pItemInfo != NULL) {
#ifdef _GAMEENGINE_3D_
               m_vpBtn[field]->setImage(pItemInfo->geticonName());

               //堆疊數量
               char buf[10];
			      sprintf_s(buf, sizeof(buf), "%d", pItem->getStack());
               m_vpBtn[field]->setText(buf, 1, 1, 1);
#elif _GAMEENGINE_2D_
               m_vpBtn[field]->str = pItemInfo->getName();

               //堆疊數量
               char buf[10] ;
			      sprintf_s(buf, sizeof (buf), "%d", pItem->getStack());
			      m_vpText[TEXT_COUNT/2 + field]->setText (buf, 1, 1, 1) ;
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
            }
         }
         else {
            m_table.erase(it);

            HotKeyItem newHotKeyItem;
            newHotKeyItem.iField = field;
            newHotKeyItem.pSkill = NULL;
            newHotKeyItem.pItem = NULL;
            newHotKeyItem.iBackpackGrid = -1;
            m_pPlayer->addHotKeyItem(newHotKeyItem);
         }
      }
   }
}

void CHotKeyWnd::updateAddSkill(CUnitObject *pUnitObject, int skillID)
{
}

void CHotKeyWnd::updateSkillAvailable(CSkill *pSkill)
{
   if(pSkill != NULL) {
      CSkillInfo *pSkillInfo = pSkill->getInfo();
      std::map<void *, int>::iterator it = m_table.find(pSkill);
      if(it != m_table.end()) {
         int field = it->second;
         if(pSkill->getAvailable() == false) {
#ifdef _GAMEENGINE_3D_
            m_vpBtn[field]->setImage(pSkillInfo->geticonName() + "/CoolDown");
#elif _GAMEENGINE_2D_
            char buf[10] ;
		      sprintf_s(buf, sizeof(buf), "不可用");
            m_vpText[TEXT_COUNT/2 + field]->setText(buf, 1, 1, 1);
#endif
         }
         else {
#ifdef _GAMEENGINE_3D_
            if(canUseSkill(pSkill) == true)
               m_vpBtn[field]->setImage(pSkillInfo->geticonName());
#elif _GAMEENGINE_2D_
            m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);
#endif
         }
      }
   }
}

void CHotKeyWnd::updateSkillCoolDown(CSkill *pSkill)
{
   if(pSkill != NULL) {
      CSkillInfo *pSkillInfo = pSkill->getInfo();
      std::map<void *, int>::iterator it = m_table.find(pSkill);
      if(it != m_table.end()) {
         int field = it->second;

         float surplusCoolDown = pSkill->getSurplus();
         if(surplusCoolDown != 0.0f) {
#ifdef _GAMEENGINE_3D_
            if(m_bvCoolDown[field] == false) {
               m_vpBtn[field]->setImage(pSkillInfo->geticonName() + "/CoolDown");
               m_bvCoolDown[field] = true;
            }
#elif _GAMEENGINE_2D_
            char buf[10] ;
		      sprintf_s(buf, sizeof(buf), "%.2f", surplusCoolDown);
            m_vpText[TEXT_COUNT/2 + field]->setText(buf, 1, 1, 1);
#endif
         }
         else {
#ifdef _GAMEENGINE_3D_
            if(m_bvCoolDown[field] == true) {
               if(canUseSkill(pSkill) == true)
                  m_vpBtn[field]->setImage(pSkillInfo->geticonName());
               m_bvCoolDown[field] = false;
            }
#elif _GAMEENGINE_2D_
            m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);
#endif
         }
      }
   }
}

void CHotKeyWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
   for(int i = 0; i < (int)m_pPlayer->getHotKeySize(); i++) {
      HotKeyItem *pHotKeyItem = m_pPlayer->getHotKeyItem(i);
      if(pHotKeyItem->pSkill != NULL) {
         std::map<void *, int>::iterator it = m_table.find(pHotKeyItem->pSkill);
         if(it != m_table.end()) {
            int field = it->second;

            CSkillInfo *pSkillInfo = pHotKeyItem->pSkill->getInfo();
#ifdef _GAMEENGINE_3D_
            if(canUseSkill(pHotKeyItem->pSkill) == true)
               m_vpBtn[field]->setImage(pSkillInfo->geticonName());
            else
               m_vpBtn[field]->setImage(pSkillInfo->geticonName() + "/CoolDown");
#elif _GAMEENGINE_2D_
            if(canUseSkill(pHotKeyItem->pSkill) == true)
               m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);
            else {
               char buf[10];
		         sprintf_s(buf, sizeof(buf), "不可用");
               m_vpText[TEXT_COUNT/2 + field]->setText(buf, 1, 1, 1);
            }
#endif
         }
      }
   }
}

#ifdef _GAMEENGINE_3D_
void CHotKeyWnd::keyDown(const OIS::KeyEvent &evt)
{
   switch(evt.key) {
      case OIS::KC_1: {
         onLCommand(0);
         break;
      }

      case OIS::KC_2: {
         onLCommand(1);
         break;
      }

      case OIS::KC_3: {
         onLCommand(2);
         break;
      }

      case OIS::KC_4: {
         onLCommand(3);
         break;
      }

      case OIS::KC_5: {
         onLCommand(4);
         break;
      }

      case OIS::KC_6: {
         onLCommand(5);
         break;
      }

      case OIS::KC_7: {
         onLCommand(6);
         break;
      }

      case OIS::KC_8: {
         onLCommand(7);
         break;
      }

      case OIS::KC_9: {
         onLCommand(8);
         break;
      }

      case OIS::KC_0: {
         onLCommand(9);
         break;
      }

      case OIS::KC_C: {
         CSkill *pSkill = m_pPlayer->getSkill(0);
         CPacketCanUseSkill packet;
         packet.pack(m_pPlayer, pSkill->getID());
         m_pNetStream->send(&packet, sizeof(packet));
         break;
      }
   }
}

void CHotKeyWnd::keyUp(const OIS::KeyEvent &evt)
{
}
#endif

bool CHotKeyWnd::canUseSkill(CSkill *pSkill)
{
   if(pSkill->getAvailable() == false)  // 確定該項技能因裝備關係而可以使用
      return false;

   if(pSkill->isReady() == false)    // 確定該項技能的冷卻時間已經完成
      return false;

   CSkillInfo *pUseSkillInfo = pSkill->getInfo();
   if(m_pPlayer->getMP() < pUseSkillInfo->getCastMP())   // 確定角色的MP足夠使用該項技能
      return false;

   return true;
}