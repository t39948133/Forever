#include "CBackpackWnd.h"
#include "CBackPack.h"

CBackpackWnd::~CBackpackWnd()
{
   if(m_pPlayer != NULL) {
      m_pPlayer->removePlayerAttrEventListener(this);
      m_pPlayer->removePlayerBackpackEventListener(this);
   }
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
   w = CELL_SIZE * BACK_ROW;
   h = CELL_SIZE * 4;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
   m_overlay.setBackImage("Examples/KAMEN-setup");

	for(int i = 0; i < BACK_COLUMN; i++) {
      for(int m = 0; m < BACK_ROW; m++) {	
         // 背包欄位
			m_vpBtn[i * BACK_ROW + m] = new CImageButton();
			m_vpBtn[i * BACK_ROW + m]->init(m_overlay, m*CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2, CELL_SIZE, CELL_SIZE, i * BACK_ROW + m) ;
			addChild(m_vpBtn[i * BACK_ROW + m]) ;

         // 堆疊數量欄位
         m_vpText[i * BACK_ROW + m] = new CTextAreaOgre();
			m_vpText[i * BACK_ROW + m]->init (m_overlay, m*CELL_SIZE+40, i*CELL_SIZE+CELL_SIZE+10, CELL_SIZE, CELL_SIZE) ;
			addChild (m_vpText[i * BACK_ROW + m]) ;
		}
   }

	//顯示此介面名稱(背包)及多少金幣	
   for(int i = BACK_MAX; i < BACK_MAX + 2; i++) {
		m_vpText[i] = new CTextAreaOgre();
		if(i == BACK_MAX) {
			m_vpText[i]->init (m_overlay, w/2-30, 0, w, CELL_SIZE) ;
			m_vpText[i]->setText ("背包", 1, 0, 0) ;
		}
      else if(i == BACK_MAX + 1) {
			m_vpText[i]->init (m_overlay, CELL_SIZE*3, CELL_SIZE*3+CELL_SIZE/2, w, CELL_SIZE) ;
		}
		addChild(m_vpText[i]) ;
	}
#elif _GAMEENGINE_2D_
	for(int i = 0; i < BACK_COLUMN; i++)
   {
		for(int m = 0; m < BACK_ROW; m++)
		{
         // 背包欄位
			m_vpBtn[i * BACK_ROW + m] = new CTextButton();
			m_vpBtn[i * BACK_ROW + m]->init(m * CELL_SIZE, i * CELL_SIZE + CELL_SIZE / 2, CELL_SIZE, CELL_SIZE, i * BACK_ROW + m);
			addChild(m_vpBtn[i * BACK_ROW + m]);

         // 堆疊數量欄位
         m_vpText[i * BACK_ROW + m] = new CTextArea() ;
			m_vpText[i * BACK_ROW + m]->init(m * CELL_SIZE, i * CELL_SIZE + CELL_SIZE, CELL_SIZE, CELL_SIZE);
         addChild(m_vpText[i * BACK_ROW + m]);
		}
   }

	//顯示此介面名稱(背包)及多少金幣			
	for (int i = BACK_MAX; i < BACK_MAX + 2; i++) 
	{
		m_vpText[i] = new CTextArea() ;
		if (i == BACK_MAX)
		{
			m_vpText[i]->init (w/2-30, 0, w, CELL_SIZE) ;
			m_vpText[i]->setText ("背包", 1, 1, 1) ;
		}else if (i == BACK_MAX + 1)
		{
			m_vpText[i]->init (CELL_SIZE*5, CELL_SIZE * BACK_COLUMN + CELL_SIZE / 2, w, CELL_SIZE) ;
		}
		addChild (m_vpText[i]) ;
	}
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   updatePlayerBackpack(m_pPlayer);
   updatePlayerAttr(m_pPlayer);
   show(false);
}

bool CBackpackWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE;
}

void CBackpackWnd::onLCommand(int btnID)
{
   // 把物品放於HotKey上
   CBackPack backpack = m_pPlayer->getBackPack(); 
   CItem *pItem = backpack.getItem(btnID);
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

void CBackpackWnd::onRCommand (int btnID)
{
   // 使用物品
   CBackPack backpack = m_pPlayer->getBackPack(); 
   CItem *pItem = backpack.getItem(btnID);
   if(pItem != NULL) {
      CItemInfo *pItemInfo = pItem->getInfo();
      if(pItemInfo != NULL) {
         m_pPlayer->useItem(pItem->getID());
      }
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

void CBackpackWnd::updatePlayerBackpack(CPlayer *pPlayer)
{
   CBackPack backpack = pPlayer->getBackPack();

   //更新背包裡的道具/堆疊數量
   for(int i = 0; i <BACK_COLUMN; i++) {
	   for(int m = 0; m < BACK_ROW; m++) {		
         CItem *pItem = backpack.getItem(i * BACK_ROW + m);
		   if(pItem != NULL) {
            CItemInfo *pItemInfo = pItem->getInfo();

#ifdef _GAMEENGINE_3D_
            if(pItemInfo != NULL)
               m_vpBtn[i * BACK_ROW + m]->setImage(pItemInfo->geticonName());
            else
               m_vpBtn[i * BACK_ROW + m]->setImage("Examples/ogreborder");
#elif _GAMEENGINE_2D_
            //道具
			   if(pItemInfo != NULL) 
               m_vpBtn[i * BACK_ROW + m]->str = pItemInfo->getName();
            else
               m_vpBtn[i * BACK_ROW + m]->str = "";
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

            //堆疊數量
            char buf[10] ;
			   sprintf_s(buf, sizeof(buf), "%d", pItem->getStack());
			   m_vpText[i * BACK_ROW + m]->setText (buf, 1, 1, 1);
		   }
	   }
   }
}

void CBackpackWnd::updatePlayerAttr(CPlayer *pPlayer)
{
   //更新多少金幣			
   char buf[20] ;
   sprintf_s(buf, sizeof(buf), "金幣      %d元", pPlayer->getMoney());
   m_vpText[BACK_MAX + 1]->setText(buf, 1, 0, 0);
}