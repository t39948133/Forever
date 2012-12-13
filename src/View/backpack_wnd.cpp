#include "backpack_wnd.h"
#include "item.h"
#include "image_button.h"

//背包視窗
void BackpackWnd::init (int _x, int _y, Player* pb)
{
	pPlayer = pb ;
	x = _x ;
	y = _y ;
	w = CELL_SIZE*8 ;
	h = CELL_SIZE*4 ;

#ifdef _PROJECT_OGRE_3D_
	overlayBP.init (x, y, w, h) ;

	for (int i = 0; i<3; i++)
		for (int m = 0; m<8; m++)
		{		
			ImageButton* pBtn = new ImageButton ;
			pBtn->init (overlayBP, m*CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2, CELL_SIZE, CELL_SIZE, i*8+m) ;
			if (i == 0 && m == 0)
			{
				pBtn->setImage ("solution_1") ;
			}else if (i == 0 && m == 1)
			{
				pBtn->setImage ("sandwich") ;
			}else 
			{
				pBtn->setImage ("ogreborder") ;
			}
			
			addChild (pBtn) ;
		}
/*
	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayBP, w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 24) ;
	//pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		char buf[256] ;

		if (i == 0)
		{
			pTA->init (overlayBP, w/2-30, 0, w, CELL_SIZE) ;
			pTA->setText ("背包", 1, 0, 0) ;
		}else if (i == 1)
		{
			pTA->init (overlayBP, CELL_SIZE, CELL_SIZE*3+CELL_SIZE/2, w, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "金幣         %d元", pPlayer->money) ;
			pTA->setText (buf, 1, 1, 1) ;
		}

		addChild (pTA) ;
	}
#else _PROJECT_GDI_
	for (int i = 0; i<3; i++)
		for (int m = 0; m<8; m++)
		{		
			TextButton* pBtn = new TextButton ;
			pBtn->init (m*CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2, CELL_SIZE, CELL_SIZE, i*8+m) ;
			Item* pItem = pPlayer->backpack.getItem (i*8+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pinfo = pItem->getInfo () ;
				if (pinfo != NULL)
				{ 
					pBtn->str = pinfo->name ;
				}
			}
			
			addChild (pBtn) ;
		}

	TextButton* pBtn = new TextButton ;
	pBtn->init (w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 24) ;
	pBtn->str = "X" ;
	addChild (pBtn) ;

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		char buf[256] ;

		if (i == 0)
		{
			pTA->init (w/2-30, 0, w, CELL_SIZE) ;
			pTA->setText ("背包", 1, 1, 1) ;
		}else if (i == 1)
		{
			pTA->init (CELL_SIZE, CELL_SIZE*3+CELL_SIZE/2, w, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "金幣         %d元", pPlayer->money) ;
			pTA->setText (buf, 1, 1, 1) ;
		}

		addChild (pTA) ;
	}

#endif
}

bool BackpackWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE/2 ;
}

void BackpackWnd::onCommand (int id)
{
	pPlayer->useItem (id) ;
}

#ifdef _PROJECT_OGRE_3D_
void BackpackWnd::onMove ()
{
	overlayBP.setPos (x, y) ;
}

void BackpackWnd::setZOrder (int z)
{
	overlayBP.setZOrder (z) ;
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
					ItemInfo* pinfo = pItem->getInfo () ;
					if (pinfo != NULL)
					{ 
						_itoa_s (pItem->getStack (), buf,
							sizeof(buf), 10) ;

						TextOut (hdc, x+m*CELL_SIZE,
									y+i*CELL_SIZE+CELL_SIZE,
									pinfo->name,
									4) ;
						TextOut (hdc, x+m*CELL_SIZE,
									y+i*CELL_SIZE+CELL_SIZE+20,
									buf, strlen (buf)) ;
					}
				}
			}
	}
*/
