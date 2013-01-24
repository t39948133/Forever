#include "CHotKeyWnd.h"
#include "CSkill.h"
#include "CItem.h"

CHotKeyWnd::~CHotKeyWnd()
{
   if(m_pPlayer != NULL)
      m_pPlayer->removePlayerHotKeyEventListener(this);
}

void CHotKeyWnd::init (int _x, int _y, CPlayer *pPlr)
{
   m_pPlayer = pPlr;
   if(m_pPlayer != NULL)
      m_pPlayer->addPlayerHotKeyEventListener(this);

   x = _x ;
	y = _y ;
	w = BUTTON_COUNT*CELL_SIZE ;
	h = CELL_SIZE ;

#ifdef _GAMEENGINE_3D_
	overlayUI.init (x, y, w, h) ;

	//熱鍵內容(食物或技能)
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new ImageButton ;
		vpBtn[i]->init (overlayUI, i*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;
		addChild (vpBtn[i]) ;
	}

	//相對應熱鍵值
	for (int i = 0; i<TEXT_COUNT/2; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, i*CELL_SIZE, 0, CELL_SIZE/2, CELL_SIZE/2) ;
		char buf[256] ;
		if (i == TEXT_COUNT/2-1)
		{
			vpText[i]->setText ("0", 1, 1, 0) ;
		}else
		{
			sprintf_s (buf, sizeof (buf), "%d", i+1) ;
			vpText[i]->setText (buf, 1, 1, 0) ;
		}
		
		addChild (vpText[i]) ;
	}

	//堆疊數量
	for (int i = TEXT_COUNT/2; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, (i-TEXT_COUNT/2)*CELL_SIZE+20, 20, CELL_SIZE/2, CELL_SIZE/2) ;		
		addChild (vpText[i]) ;
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
         if(pItemInfo != NULL)
            m_pPlayer->useItem(pHotKeyItem->pItem->getID());
      }
      else if(pHotKeyItem->pSkill != NULL) {
         if(m_pPlayer->canUseSkill(pHotKeyItem->pSkill->getID()) == true) {
            m_pPlayer->startCastSkill(pHotKeyItem->pSkill->getID());
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

#ifdef _GAMEENGINE_3D_
void CHotKeyWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

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
#elif _GAMEENGINE_2D_
            m_vpBtn[pHotKeyItem->iField]->str = pItemInfo->getName();
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

            //堆疊數量
            char buf[10] ;
			   sprintf_s(buf, sizeof (buf), "%d", pHotKeyItem->pItem->getStack());
			   m_vpText[TEXT_COUNT/2 + pHotKeyItem->iField]->setText (buf, 1, 1, 1) ;

            m_table.insert(std::pair<void *, int>(pHotKeyItem->pItem, pHotKeyItem->iField));
         }
      }
   }
   else {
#ifdef _GAMEENGINE_3D_
         m_vpBtn[pHotKeyItem->iField]->setImage("Examples/ogreborder");
#elif _GAMEENGINE_2D_
         m_vpBtn[pHotKeyItem->iField]->str = "";
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

         m_vpText[TEXT_COUNT/2 + pHotKeyItem->iField]->setText("", 1, 1, 1);
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
#elif _GAMEENGINE_2D_
               m_vpBtn[field]->str = pItemInfo->getName();
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

               //堆疊數量
               char buf[10] ;
			      sprintf_s(buf, sizeof (buf), "%d", pItem->getStack());
			      m_vpText[TEXT_COUNT/2 + field]->setText (buf, 1, 1, 1) ;
            }
         }
         else {
            m_table.erase(it);

            HotKeyItem newHotKeyItem;
            newHotKeyItem.iField = field;
            newHotKeyItem.pSkill = NULL;
            newHotKeyItem.pItem = NULL;
            m_pPlayer->addHotKeyItem(newHotKeyItem);
         }
      }
   }
}

void CHotKeyWnd::updateSkill(CUnitObject *pUnitObject)
{
}

void CHotKeyWnd::updateSkillCoolDown(CSkill *pSkill)
{
   if(pSkill != NULL) {
      std::map<void *, int>::iterator it = m_table.find(pSkill);
      if(it != m_table.end()) {
         int field = it->second;

         float surplusCoolDown = pSkill->getSurplus();
         if(surplusCoolDown != 0.0f) {
            char buf[10] ;
		      sprintf_s(buf, sizeof(buf), "%.2f", surplusCoolDown);
            m_vpText[TEXT_COUNT/2 + field]->setText(buf, 1, 1, 1);
         }
         else
            m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);
      }
   }
}