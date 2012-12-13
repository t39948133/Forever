#include "player_status_wnd.h"

	void PlayerStatusWnd::init (int _x, int _y, UnitData* pu)
	{
		pUnitData = pu ;

		x = _x ;
		y = _y ;

		w = 200 ;
		h = 100 ;
	}

	void PlayerStatusWnd::draw (HDC hdc)
	{
		Window::draw (hdc, 0, 0) ;
		char buf[256] ;
		sprintf_s (buf, sizeof(buf), "hp:%d", pUnitData->hp) ;
		TextOut (hdc, x+2, y+2, buf, strlen (buf)) ;
		sprintf_s (buf, sizeof(buf), "mp:%d", pUnitData->mp) ;
		TextOut (hdc, x+2, y+2+20, buf, strlen (buf)) ;
	}
