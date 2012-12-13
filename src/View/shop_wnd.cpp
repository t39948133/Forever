#include "shop_wnd.h"
#include "item.h"


void ShopWnd::init (int _x, int _y, Player* pb)
	{
		pPlayer = pb ;
		x = _x ;
		y = _y ;

		w = CELL_W_COUNT*CELL_SIZE ;
		h = CELL_H_COUNT*CELL_SIZE+CELL_SIZE ;
	}

bool ShopWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE ;
}

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
