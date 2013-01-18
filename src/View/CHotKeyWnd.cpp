#include "CHotKeyWnd.h"
#include "CSkill.h"
#include "CItem.h"
#include "CWindowMan.h"

CHotKeyWnd::~CHotKeyWnd()
{
   if(m_pPlayer != NULL)
      m_pPlayer->removeModelEventListener(this);
}

void CHotKeyWnd::init (int _x, int _y, CPlayer *pPlr)
{
   m_pPlayer = pPlr;
   m_pPlayer->addModelEventListener(this);

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
      HotKeyItem newHotKeyItem;
      newHotKeyItem.pSkill = NULL;
      newHotKeyItem.pItem = NULL;
      m_pPlayer->addHotKeyItem(btnID, newHotKeyItem);
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

void CHotKeyWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
}

void CHotKeyWnd::updateBackpack(CUnitObject *pUnitObject)
{
}

void CHotKeyWnd::updateSkill(CUnitObject *pUnitObject)
{
}

void CHotKeyWnd::updateHotKeyItem(int field, HotKeyItem *pHotKeyItem)
{
   if(pHotKeyItem->pSkill != NULL) {
      CSkillInfo *pSkillInfo = pHotKeyItem->pSkill->getInfo();

      if(pSkillInfo != NULL) {
#ifdef _GAMEENGINE_3D_
         m_vpBtn[field]->setImage(pSkillInfo->geticonName());
#elif _GAMEENGINE_2D_
         m_vpBtn[field]->str = pSkillInfo->getName();
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

         // 技能冷卻時間倒數
         float surplusCoolDown = pHotKeyItem->pSkill->getSurplus();
         if(surplusCoolDown != 0.0f) {
            char buf[10] ;
			   sprintf_s(buf, sizeof(buf), "%.2f", surplusCoolDown);
            m_vpText[TEXT_COUNT/2 + field]->setText(buf, 1, 1, 1);
         }
         else
            m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);
      }
   }
   else if(pHotKeyItem->pItem != NULL) {
      if(pHotKeyItem->pItem->getStack() > 0) {
         CItemInfo *pItemInfo = pHotKeyItem->pItem->getInfo();

         if(pItemInfo != NULL) {
#ifdef _GAMEENGINE_3D_
            m_vpBtn[field]->setImage(pItemInfo->geticonName());
#elif _GAMEENGINE_2D_
            m_vpBtn[field]->str = pItemInfo->getName();
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

            //堆疊數量
            char buf[10] ;
			   sprintf_s(buf, sizeof (buf), "%d", pHotKeyItem->pItem->getStack());
			   m_vpText[TEXT_COUNT/2 + field]->setText (buf, 1, 1, 1) ;
         }
      }
      else {
         HotKeyItem newHotKeyItem;
         newHotKeyItem.pSkill = NULL;
         newHotKeyItem.pItem = NULL;
         m_pPlayer->addHotKeyItem(field, newHotKeyItem);

#ifdef _GAMEENGINE_3D_
         m_vpBtn[field]->setImage("Examples/ogreborder");
#elif _GAMEENGINE_2D_
         m_vpBtn[field]->str = "";
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

         m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);
      }
   }
   else {
#ifdef _GAMEENGINE_3D_
         m_vpBtn[field]->setImage("Examples/ogreborder");
#elif _GAMEENGINE_2D_
         m_vpBtn[field]->str = "";
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

         m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);
   }
}

void CHotKeyWnd::updateCoolDown(CSkill *pSkill)
{
   int field = 0;
   for(field = 0; field < m_pPlayer->getHotKeySize(); field++) {
      HotKeyItem *pHotKeyItem = m_pPlayer->getHotKeyItem(field);
      if(pHotKeyItem != NULL) {
         if(pHotKeyItem->pSkill == pSkill) {
            // 技能冷卻時間倒數
            float surplusCoolDown = pHotKeyItem->pSkill->getSurplus();
            if(surplusCoolDown != 0.0f) {
               char buf[10] ;
			      sprintf_s(buf, sizeof(buf), "%.2f", surplusCoolDown);
               m_vpText[TEXT_COUNT/2 + field]->setText(buf, 1, 1, 1);
            }
            else
               m_vpText[TEXT_COUNT/2 + field]->setText("", 1, 1, 1);

            return;
         }
      }
   }
}