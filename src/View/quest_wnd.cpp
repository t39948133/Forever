#include "quest_wnd.h"

#include "backpack_wnd.h"
#include "item.h"

//­I¥]µøµ¡
void QuestWnd::init (int _x, int _y, Player* pb)
	{
		pPlayer = pb ;
		x = _x ;
		y = _y ;

		w = 200 ;
		h = CELL_H_COUNT*CELL_SIZE+CELL_SIZE ;

		/*
		for (int i = 0; i<4; i++)
			for (int m = 0; m<4; m++)
			{
				Button* pBtn = new Button ;
				pBtn->x = m*CELL_SIZE ;
				pBtn->y = (i+1)*CELL_SIZE ;
				pBtn->w = CELL_SIZE ;
				pBtn->h = CELL_SIZE ;
				pBtn->id = i*4+m ;

				addChild (pBtn) ;
			}
		*/
	}

bool QuestWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE ;
}

void QuestWnd::draw (HDC hdc, int ox, int oy)
{
	Window::draw (hdc, ox, oy) ;

	int i = 0 ;
	V_QUEST::iterator pi = pPlayer->questMap.vQuest.begin () ;
	while (pi != pPlayer->questMap.vQuest.end ())
	{
		QuestInfo* pinfo = pi->getInfo () ;

		TextOut (hdc, 2+x, 2+y+(i+1)*CELL_SIZE, pinfo->name,
					pinfo->name.length ()) ;

		++ pi ;
		i ++ ;
	}
}

/*
void QuestWnd::onCommand (int id)
{
	pPlayer->useItem (id) ;
}
*/

/*
void QuestWnd::onClick (int tx, int ty)
{
	int offset = tx/CELL_SIZE+
		(ty-CELL_SIZE)/CELL_SIZE*CELL_W_COUNT ;

	pPlayer->useItem (offset) ;
}
*/

/*
	void QuestWnd::draw (HDC hdc)
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