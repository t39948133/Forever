#include "CBackpackWnd.h"
#include "CBackpack.h"

CBackpackWnd::CBackpackWnd()
{
#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
      m_vpBtn[i] = NULL;
      m_vpStackText[i] = NULL;
   }

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
#endif
}

CBackpackWnd::~CBackpackWnd()
{
   if(m_pPlayer != NULL) {
      m_pPlayer->removePlayerAttrEventListener(this);
      m_pPlayer->removePlayerBackpackEventListener(this);
   }

#ifdef _GAMEENGINE_3D_
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
#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }

      if(m_vpStackText[i] != NULL) {
         delete m_vpStackText[i];
         m_vpStackText[i] = NULL;
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

void CBackpackWnd::init(int _x, int _y, CPlayer *pb)
{	
	m_pPlayer = pb ;
   if(m_pPlayer != NULL) {
      m_pPlayer->addPlayerAttrEventListener(this);
      m_pPlayer->addPlayerBackpackEventListener(this);
   }

   x = _x;
   y = _y;
   w = 408;
   h = 201;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
   m_overlay.setBackImage("UI/BG/BackpackWnd");

	for(int i = 0; i < BACK_COLUMN; i++) {
      for(int m = 0; m < BACK_ROW; m++) {	
         // 背包欄位
			m_vpBtn[i * BACK_ROW + m] = new CImageButton();
			m_vpBtn[i * BACK_ROW + m]->init(&m_overlay, 11 + m * ICON_SIZE + 3 * m, 
                                                     33 + i * ICON_SIZE + 3 * i, ICON_SIZE, ICON_SIZE, i * BACK_ROW + m);
         m_vpBtn[i * BACK_ROW + m]->setTextVisible(true);
         m_vpBtn[i * BACK_ROW + m]->setTextHorizontalAlignment(CImageButton::H_RIGHT);
         m_vpBtn[i * BACK_ROW + m]->setTextVerticalAlignment(CImageButton::V_BOTTOM);
			addChild(m_vpBtn[i * BACK_ROW + m]);
		}
   }

	//顯示此介面名稱(背包)及多少金幣	
   for(int i = TEXT_TITLE; i < TEXT_COUNT; i++) {
		m_vpText[i] = new CTextAreaOgre();
		
      switch(i) {
         case TEXT_TITLE:
			   m_vpText[i]->init(&m_overlay, 0, 0, w, 25);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
			   m_vpText[i]->setText("背包", 1, 1, 1);
            break;
		
         case TEXT_MONEY:
			   m_vpText[i]->init(&m_overlay, 200, 173, 154, 20);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_RIGHT);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            break;
      }

		addChild(m_vpText[i]);
	}
#elif _GAMEENGINE_2D_
	for(int i = 0; i < BACK_COLUMN; i++) {
		for(int m = 0; m < BACK_ROW; m++) {
         // 背包欄位
			m_vpBtn[i * BACK_ROW + m] = new CTextButton();
			m_vpBtn[i * BACK_ROW + m]->init(11 + m * ICON_SIZE + 3 * m,
                                         33 + i * ICON_SIZE + 3 * i, ICON_SIZE, ICON_SIZE, i * BACK_ROW + m);
			addChild(m_vpBtn[i * BACK_ROW + m]);

         // 堆疊數量欄位
         m_vpStackText[i * BACK_ROW + m] = new CTextArea();
			m_vpStackText[i * BACK_ROW + m]->init(11 + m * ICON_SIZE + 3 * m + 20, 33 + i * ICON_SIZE + 3 * i + 20, 20, 20);
         m_vpStackText[i]->setAlignment(CTextArea::RIGHT);
         addChild(m_vpStackText[i * BACK_ROW + m]);
		}
   }

   //顯示此介面名稱(背包)及多少金幣	
   for(int i = TEXT_TITLE; i < TEXT_COUNT; i++) {
		m_vpText[i] = new CTextArea();
		
      switch(i) {
         case TEXT_TITLE:
			   m_vpText[i]->init(0, 0, w, 25);
            m_vpText[i]->setAlignment(CTextArea::CENTER);
			   m_vpText[i]->setText("背包", 1, 1, 1);
            break;
		
         case TEXT_MONEY:
			   m_vpText[i]->init(200, 173, 154, 20);
            break;
      }

		addChild(m_vpText[i]);
	}
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   updatePlayerBackpack(m_pPlayer->getBackpack());
   updatePlayerAttr(m_pPlayer);
   show(false);
}

bool CBackpackWnd::canDrag(int tx, int ty)
{
	return ty < 25;
}

void CBackpackWnd::onLCommand(int btnID)
{
   // 把物品放於HotKey上
   CBackpack *pBackpack = m_pPlayer->getBackpack(); 
   CItem *pItem = pBackpack->getItem(btnID);
   if(pItem != NULL) {
      for(int i = 0; i < m_pPlayer->getHotKeySize(); i++) {
         HotKeyItem *pHotKeyItem = m_pPlayer->getHotKeyItem(i);
         
         if(pHotKeyItem != NULL) {
            if((pHotKeyItem->pItem == NULL) && (pHotKeyItem->pSkill == NULL)) {
               HotKeyItem newHotKeyItem;
               newHotKeyItem.iField = i;
               newHotKeyItem.pItem = pItem;
               newHotKeyItem.pSkill = NULL;
               m_pPlayer->addHotKeyItem(newHotKeyItem);

               break;
            }
         }
      }
   }
}

void CBackpackWnd::onRCommand(int btnID)
{
   // 使用物品
   CBackpack *pBackpack = m_pPlayer->getBackpack(); 
   CItem *pItem = pBackpack->getItem(btnID);
   if(pItem != NULL) {
      CItemInfo *pItemInfo = pItem->getInfo();

      if(pItemInfo != NULL)
         m_pPlayer->useItem(pItem->getID());
   }
}

WindowClassType CBackpackWnd::getClassType()
{
   return WND_BACKPACK;
}

void CBackpackWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

void CBackpackWnd::onDrag()
{
#ifdef _GAMEENGINE_3D_
	m_overlay.setPos(x, y);
#endif  // #ifdef _GAMEENGINE_3D_
}

#ifdef _GAMEENGINE_3D_
void CBackpackWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

void CBackpackWnd::updatePlayerBackpack(CBackpack *pBackpack)
{
   //更新背包裡的道具/堆疊數量
   for(int i = 0; i <BACK_COLUMN; i++) {
	   for(int m = 0; m < BACK_ROW; m++) {		
         CItem *pItem = pBackpack->getItem(i * BACK_ROW + m);
		   if(pItem != NULL) {
            CItemInfo *pItemInfo = pItem->getInfo();

#ifdef _GAMEENGINE_3D_
            if(pItemInfo != NULL)
               m_vpBtn[i * BACK_ROW + m]->setImage(pItemInfo->geticonName());
            else
               m_vpBtn[i * BACK_ROW + m]->setImage("UI/Icon/NullBackpack");
#elif _GAMEENGINE_2D_
            //道具
			   if(pItemInfo != NULL) 
               m_vpBtn[i * BACK_ROW + m]->str = pItemInfo->getName();
            else
               m_vpBtn[i * BACK_ROW + m]->str = "";
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

            if(pItem->getStack() > 0) {
               //堆疊數量
               char buf[10] ;
			      sprintf_s(buf, sizeof(buf), "%d", pItem->getStack());
#ifdef _GAMEENGINE_3D_
               m_vpBtn[i * BACK_ROW + m]->setText(buf, 1, 1, 1);
#elif _GAMEENGINE_2D_
               m_vpStackText[i * BACK_ROW + m]->setText(buf, 1, 1, 1);
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
            }
            else {
#ifdef _GAMEENGINE_3D_
               m_vpBtn[i * BACK_ROW + m]->setText("", 1, 1, 1);
#elif _GAMEENGINE_2D_
               m_vpStackText[i * BACK_ROW + m]->setText("", 1, 1, 1);
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
            }
		   }
	   }
   }
}

void CBackpackWnd::updatePlayerAttr(CPlayer *pPlayer)
{
   //更新多少金幣			
   char buf[20];
#ifdef _GAMEENGINE_3D_
   sprintf_s(buf, sizeof(buf), "%d", pPlayer->getMoney());
#elif _GAMEENGINE_2D_
   sprintf_s(buf, sizeof(buf), "金錢   %7d", pPlayer->getMoney());
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
   m_vpText[TEXT_MONEY]->setText(buf, 1, 1, 1);
}