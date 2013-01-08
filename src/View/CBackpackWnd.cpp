#include "CBackpackWnd.h"
#include "CBackPack.h"

void CBackpackWnd::init(int _x, int _y, CPlayer *pb)
{	
   bVisible = false;
	pPlayer = pb ;

   x = _x;
   y = _y;
   w = CELL_SIZE * BACK_ROW;
   h = CELL_SIZE * 4;

#ifdef _GAMEENGINE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.getOverlay ()->hide () ;
	overlayUI.setImage ("KAMEN-stup") ;

	for (int i = 0; i<3; i++)
		for (int m = 0; m<8; m++)
		{		
			vpBtn[i*8+m] = new ImageButton ;
			vpBtn[i*8+m]->init (overlayUI, m*CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2, CELL_SIZE, CELL_SIZE, i*8+m) ;
			Item* pItem = pPlayer->backpack.getItem (i*8+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{
					vpBtn[i*8+m]->setImage ((const Ogre::String)pInfo->image) ;
				}
			}
						
			addChild (vpBtn[i*8+m]) ;
		}
/*
	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayUI, w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 24) ;
	//pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	//顯示堆疊數量
	for (int i = 0; i<3; i++)
		for (int m = 0; m<8; m++)
		{		
			vpText[i*8+m] = new TextArea ;
			vpText[i*8+m]->init (overlayUI, m*CELL_SIZE+40, i*CELL_SIZE+CELL_SIZE+10, CELL_SIZE, CELL_SIZE) ;
			Item* pItem = pPlayer->backpack.getItem (i*8+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{ 
					char buf[256] ;
					sprintf_s (buf, sizeof (buf), "%d", pItem->getStack ()) ;
					vpText[i*8+m]->setText (buf, 0, 1, 0) ;
				}
			}
			
			addChild (vpText[i*8+m]) ;
		}
	//顯示此介面名稱(背包)及多少金幣	
	for (int i = 0; i<2; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;

		if (i == 0)
		{
			vpText[i]->init (overlayUI, w/2-30, 0, w, CELL_SIZE) ;
			vpText[i]->setText ("背包", 1, 0, 0) ;
		}else if (i == 1)
		{
			vpText[i]->init (overlayUI, CELL_SIZE*3, CELL_SIZE*3+CELL_SIZE/2, w, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "金幣         %d元", pPlayer->money) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}

		addChild (vpText[i]) ;
	}
#elif _GAMEENGINE_2D_
	for(int i = 0; i < BACK_COLUMN; i++)
   {
		for(int m = 0; m < BACK_ROW; m++)
		{
         // 背包欄位
			vpBtn[i * BACK_ROW + m] = new CTextButton();
			vpBtn[i * BACK_ROW + m]->init(m * CELL_SIZE, i * CELL_SIZE + CELL_SIZE / 2, CELL_SIZE, CELL_SIZE, i * BACK_ROW + m);
			addChild(vpBtn[i * BACK_ROW + m]);

         // 堆疊數量欄位
         vpText[i * BACK_ROW + m] = new CTextArea() ;
			vpText[i * BACK_ROW + m]->init(m * CELL_SIZE, i * CELL_SIZE + CELL_SIZE, CELL_SIZE, CELL_SIZE);
         addChild(vpText[i * BACK_ROW + m]);
		}
   }

	//顯示此介面名稱(背包)及多少金幣			
	for (int i = BACK_MAX; i < BACK_MAX + 2; i++) 
	{
		vpText[i] = new CTextArea() ;
		if (i == BACK_MAX)
		{
			vpText[i]->init (w/2-30, 0, w, CELL_SIZE) ;
			vpText[i]->setText ("背包", 1, 1, 1) ;
		}else if (i == BACK_MAX + 1)
		{
			vpText[i]->init (CELL_SIZE*5, CELL_SIZE * BACK_COLUMN + CELL_SIZE / 2, w, CELL_SIZE) ;
		}
		addChild (vpText[i]) ;
	}
#endif
}

bool CBackpackWnd::canDrag (int tx, int ty)
{
	return false ;
}

void CBackpackWnd::onRCommand (int id)
{
   CBackPack backpack = pPlayer->getBackPack(); 
   CItem *pItem = backpack.getItem(id);
   if(pItem != NULL) {
      CItemInfo *pItemInfo = pItem->getInfo();
      if(pItemInfo != NULL)
         pPlayer->useItem(pItem->getID());
   }
	/*Item* pItem = pPlayer->backpack.getItem (id) ;
	if (pItem != NULL)
	{
		ItemInfo* pInfo = pItem->getInfo () ;
		if (pInfo != NULL)
		{ 
			int itemID = pItem->getID () ;
			if (pInfo->type == ItemInfo::ITEM_EQUIP)
			{
				//穿上去,背包格子編號,
//				pPlayer->wearEquip (itemID) ;
				ppinWnd->wearEquip (itemID) ;
				pItem->clear () ;
#ifdef _PROJECT_OGRE_3D_
				vpBtn[id]->setImage ("ogreborder") ;
#else _PROJECT_GDI_
				vpBtn[id]->str = "" ;
#endif
				vpText[id]->setText ("", 0, 1, 0) ;
			}else if (pInfo->type == ItemInfo::ITEM_FOOD)
			{
				//可以吃的,道具編號				
				phkWnd->addFoodHotKey (id, itemID) ;
			}
		}
	}*/
}

#ifdef _GAMEENGINE_3D_
void CBackpackWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void CBackpackWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void CBackpackWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

// Add by Darren on 2013/01/07 {
WindowClassType CBackpackWnd::getClassType()
{
   return WND_BACKPACK;
}

#ifdef _GAMEENGINE_2D_
void CBackpackWnd::draw(HDC hdc, int ox, int oy)
{
   CBackPack backpack = pPlayer->getBackPack();

   //更新背包裡的道具/堆疊數量
	for (int i = 0; i <BACK_COLUMN; i++)
   {
		for (int m = 0; m < BACK_ROW; m++)
		{		
         CItem *pItem = backpack.getItem(i * BACK_ROW + m);
			if (pItem != NULL)
			{
            CItemInfo *pItemInfo = pItem->getInfo();

            //道具
				if(pItemInfo != NULL) 
               vpBtn[i * BACK_ROW + m]->str = pItemInfo->getName();
            else
               vpBtn[i * BACK_ROW + m]->str = "";

            //堆疊數量
            char buf[10] ;
				sprintf_s (buf, sizeof (buf), "%d", pItem->getStack()) ;
				vpText[i * BACK_ROW + m]->setText (buf, 1, 1, 1) ;
			}
		}
   }

   //更新多少金幣			
	char buf[20] ;
   sprintf_s (buf, sizeof (buf), "金幣      %d元", pPlayer->getMoney()) ;
	vpText[BACK_MAX + 1]->setText (buf, 1, 1, 1) ;

   CWindow::draw(hdc, ox, oy);
}
#endif
// } Add by Darren Chen on 2013/01/07