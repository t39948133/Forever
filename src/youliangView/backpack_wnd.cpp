#include "backpack_wnd.h"
#include "hotkey_wnd.h"
#include "item.h"
#include "image_button.h"
#include "player_info_wnd.h"


//背包視窗
void BackpackWnd::init (int _x, int _y, Player* pb, HotKeyWnd* pw, PlayerInfoWnd* pw2)
{	
	bVisible = false ;
	pPlayer = pb ;
	phkWnd = pw ;
	ppinWnd = pw2 ;

	x = _x ;
	y = _y ;
	w = CELL_SIZE*8 ;
	h = CELL_SIZE*4 ;

#ifdef _PROJECT_OGRE_3D_
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
#else _PROJECT_GDI_
	//顯示背包裡的道具
	for (int i = 0; i<3; i++)
		for (int m = 0; m<8; m++)
		{		
			vpBtn[i*8+m] = new TextButton ;
			vpBtn[i*8+m]->init (m*CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2, CELL_SIZE, CELL_SIZE, i*8+m) ;
			Item* pItem = pPlayer->backpack.getItem (i*8+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{ 
					vpBtn[i*8+m]->str = pInfo->name ;
				}
			}			
			addChild (vpBtn[i*8+m]) ;
		}

	//顯示堆疊數量
	for (int i = 0; i<3; i++)
		for (int m = 0; m<8; m++)
		{		
			vpText[i*8+m] = new TextArea ;
			vpText[i*8+m]->init (m*CELL_SIZE, i*CELL_SIZE+CELL_SIZE, CELL_SIZE, CELL_SIZE) ;
			Item* pItem = pPlayer->backpack.getItem (i*8+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{ 
					char buf[256] ;
					sprintf_s (buf, sizeof (buf), "%d", pItem->getStack ()) ;
					vpText[i*8+m]->setText (buf, 1, 1, 1) ;
				}
			}			
			addChild (vpText[i*8+m]) ;
		}

	//顯示此介面名稱(背包)及多少金幣			
	for (int i = 24; i<26; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;
		if (i == 0)
		{
			vpText[i]->init (w/2-30, 0, w, CELL_SIZE) ;
			vpText[i]->setText ("背包", 1, 1, 1) ;
		}else if (i == 1)
		{
			vpText[i]->init (CELL_SIZE*5, CELL_SIZE*3+CELL_SIZE/2, w, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "金幣      %d元", pPlayer->money) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}

#endif
}

bool BackpackWnd::canDrag (int tx, int ty)
{
	return false ;
}

void BackpackWnd::onCommand (int id)
{
	Item* pItem = pPlayer->backpack.getItem (id) ;
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
	}
}

#ifdef _PROJECT_OGRE_3D_
void BackpackWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void BackpackWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void BackpackWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

/*
void BackpackWnd::onClick (int tx, int ty)
{
	int offset = tx/CELL_SIZE+
		(ty-CELL_SIZE)/CELL_SIZE*CELL_W_COUNT ;

	pPlayer->useItem (offset) ;
}
*/

/*	void BackpackWnd::draw (HDC hdc, int ox, int oy)
	{
		Window::draw (hdc, 0, 0) ;

		char buf[256] ;

		for (int i = 0; i<4; i++)
			for (int m = 0; m<4; m++)
			{
				Rectangle (hdc, x+m*CELL_SIZE,
								y+i*CELL_SIZE+CELL_SIZE,
								x+(m+1)*CELL_SIZE,
								y+(i+1)*CELL_SIZE+CELL_SIZE) ;
			}

		for (int i = 0; i<4; i++)
			for (int m = 0; m<4; m++)
			{
//				int itemID = pPlayer->backpack.vItemID[i*4+m] ;
//				if (itemID != -1)
				Item* pItem = pPlayer->backpack.getItem (i*4+m) ;
				if (pItem != NULL)
				{
					ItemInfo* pInfo = pItem->getInfo () ;
					if (pInfo != NULL)
					{ 
						_itoa_s (pItem->getStack (), buf,
							sizeof(buf), 10) ;

						TextOut (hdc, x+m*CELL_SIZE,
									y+i*CELL_SIZE+CELL_SIZE,
									pInfo->name,
									4) ;
						TextOut (hdc, x+m*CELL_SIZE,
									y+i*CELL_SIZE+CELL_SIZE+20,
									buf, strlen (buf)) ;
					}
				}
			}
	}
*/
