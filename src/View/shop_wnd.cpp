#include "shop_wnd.h"
#include "item.h"
#include "image_button.h"


void ShopWnd::init (int _x, int _y, Player* pb)
{
	bVisible = true ;
	pPlayer = pb ;
	x = _x ;
	y = _y ;
	w = CELL_SIZE*8 ;
	h = CELL_SIZE*6 ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("KAMEN-stup") ;

	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			ImageButton* pBtn = new ImageButton ;
			pBtn->init (overlayUI, m*CELL_SIZE*4, i*CELL_SIZE+CELL_SIZE/2,
				CELL_SIZE, CELL_SIZE, i*2+m) ;
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

	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			ImageButton* pBtn = new ImageButton ;
			pBtn->init (overlayUI, m*CELL_SIZE*4+CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2,
				CELL_SIZE*3, CELL_SIZE, i*2+m) ;
			if (i == 0 && m == 0)
			{
				pBtn->setImage ("ogreborder") ;		
			}else if (i == 0 && m == 1)
			{
				pBtn->setImage ("ogreborder") ;		
			}else 
			{
				pBtn->setImage ("ogreborder") ;	
			}
			
			addChild (pBtn) ;
		}

	for (int i = 0; i<2; i++)
	{		
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlayUI, i*CELL_SIZE*2+CELL_SIZE*4, CELL_SIZE*5+CELL_SIZE/2,
			CELL_SIZE*2, CELL_SIZE/2, i) ;
		pBtn->setImage ("ogreborder") ;	
		addChild (pBtn) ;
	}
/*
	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayUI, w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 22) ;
	//pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			TextArea* pTA = new TextArea ;
			pTA->init (overlayUI, m*CELL_SIZE*4+CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2,
				CELL_SIZE*3, CELL_SIZE) ;
			if (i == 0 && m == 0)
			{
				pTA->setText ("藥水", 0, 0, 1) ;	
			}else if (i == 0 && m == 1)
			{
				pTA->setText ("", 0, 0, 1) ;	
			}else 
			{
				pTA->setText ("", 0, 0, 1) ;
			}
				
			addChild (pTA) ;
		}

	for (int i = 0; i<2; i++)
	{		
		TextArea* pTA = new TextArea ;
		pTA->init (overlayUI, i*CELL_SIZE*2+CELL_SIZE*4+55, CELL_SIZE*5+CELL_SIZE/2+5,
			CELL_SIZE*2, CELL_SIZE/2) ;
		if (i == 0)
		{
			pTA->setText ("購買", 0, 0, 1) ;	
		}else if (i == 1)
		{
			pTA->setText ("結束", 0, 0, 1) ;	
		}

		addChild (pTA) ;
	}

	TextArea* pTA = new TextArea ;
	pTA->init (overlayUI, w/2-30, 5, CELL_SIZE, CELL_SIZE) ;
	pTA->setText ("商店", 1, 1, 1) ;
	addChild (pTA) ;
		
#else _PROJECT_GDI_
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			TextButton* pBtn = new TextButton ;
			pBtn->init (m*CELL_SIZE*4, i*CELL_SIZE+CELL_SIZE/2,
				CELL_SIZE, CELL_SIZE, i*2+m) ;

			ItemInfo* pInfo = Item::getInfo (i*2+m) ;
			if (pInfo != NULL)
			{
				pBtn->str = pInfo->name ;				
			}
			addChild (pBtn) ;
		}

	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			TextButton* pBtn = new TextButton ;
			pBtn->init (m*CELL_SIZE*4+CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2,
				CELL_SIZE*3, CELL_SIZE, i*2+m) ;	
		
			addChild (pBtn) ;			
		}	

	for (int i = 0; i<2; i++)
	{		
		TextButton* pBtn = new TextButton ;
		pBtn->init (i*CELL_SIZE*2+CELL_SIZE*4, CELL_SIZE*5+CELL_SIZE/2,
			CELL_SIZE*2, CELL_SIZE/2, i) ;
		addChild (pBtn) ;
	}
/*
	TextButton* pBtn = new TextButton ;
	pBtn->init (w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 22) ;
	//pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			TextArea* pTA = new TextArea ;
			pTA->init (m*CELL_SIZE*4+CELL_SIZE, i*CELL_SIZE+CELL_SIZE/2,
				CELL_SIZE*3, CELL_SIZE) ;

			ItemInfo* pInfo = Item::getInfo (i*2+m) ;
			if (pInfo != NULL)
			{
				char buf[256] ;
				sprintf_s (buf, sizeof (buf), "%s  價格 %d元", (const char*)pInfo->name, pInfo->money) ;
				pTA->setText (buf, 0, 0, 1) ;	
				addChild (pTA) ;
			}
		}

	for (int i = 0; i<2; i++)
	{		
		TextArea* pTA = new TextArea ;
		pTA->init (i*CELL_SIZE*2+CELL_SIZE*4, CELL_SIZE*5+CELL_SIZE/2,
			CELL_SIZE*2, CELL_SIZE/2) ;
		if (i == 0)
		{
			pTA->setText ("購買", 0, 0, 1) ;	
		}else if (i == 1)
		{
			pTA->setText ("結束", 0, 0, 1) ;	
		}

		addChild (pTA) ;
	}

	TextArea* pTA = new TextArea ;
	pTA->init (w/2-30, 5, CELL_SIZE, CELL_SIZE) ;
	pTA->setText ("商店", 0, 0, 1) ;
	addChild (pTA) ;
	

#endif
}

bool ShopWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE ;
}

void ShopWnd::onCommand (int id)
{
}

#ifdef _PROJECT_OGRE_3D_
void ShopWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void ShopWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void ShopWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif
/*
void ShopWnd::onClick (int tx, int ty)
{
	int offset = tx/CELL_SIZE+
		(ty-CELL_SIZE)/CELL_SIZE*CELL_W_COUNT ;

	ItemInfo* pinfo = Item::getInfo (offset) ;
	if (pinfo != NULL)
	{
		enum {BUY_COUNT = 7} ;
		int count = BUY_COUNT ;
		int totalCost = BUY_COUNT*pinfo->money ;
		if (totalCost <= pPlayer->money)
		{
			int pos = 0 ;
			pPlayer->backpack.addItem (offset, pos, count) ;

			pPlayer->money -= 
				(BUY_COUNT-count)*pinfo->money ;
		}
	}
}

	void ShopWnd::draw (HDC hdc, int ox, int oy)
	{
		Window::draw (hdc, ox, oy) ;

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
				ItemInfo* pinfo = Item::getInfo (i*4+m) ;
				if (pinfo != NULL)
				{ 
					_itoa_s (pinfo->money, buf, sizeof(buf), 10) ;
					TextOut (hdc, x+m*CELL_SIZE,
								y+i*CELL_SIZE+CELL_SIZE,
								pinfo->name,
								4) ;
					TextOut (hdc, x+m*CELL_SIZE,
								y+i*CELL_SIZE+CELL_SIZE+20,
								buf, strlen (buf)) ;
				}
			}

		_itoa_s (pPlayer->money, buf, sizeof(buf), 10) ;
		TextOut (hdc, x+2, y+2, buf, strlen (buf)) ;
	}
*/
