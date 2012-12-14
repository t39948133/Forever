#include "player_name_wnd.h"
#include "image_button.h"

void PlayerNameWnd::init (int _x, int _y, UnitData* pu)
{
	pUnitData = pu ;
	x = _x ;
	y = _y ;
	w = CELL_SIZE*CELL_W_COUNT ;
	h = CELL_SIZE*CELL_H_COUNT ;

#ifdef _PROJECT_OGRE_3D_
/*		overlay.init (x, y, w, h) ;

		TextArea* pTA = new TextArea ;			
		pTA->init (0, 0, w, h) ;
		pTA->setText ("玩家名字", 1, 1, 1) ;
		addChild (pTA) ;

		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlay, (i+1)*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;
		
		if (i == 0)
			pBtn->setImage ("img_backpack") ;
		else if (i == 1)
			pBtn->setImage ("img_skill") ;
		else if (i == 2)
			pBtn->setImage ("img_status") ;
		else if (i == 3)
			pBtn->setImage ("img_shp") ;
		addChild (pBtn) ;
*/	
#else _PROJECT_GDI_
		TextButton* pBtn = new TextButton ;
		pBtn->init (0, 0, w, h, 0) ;
		pBtn->str = "玩家名字" ;
		addChild (pBtn) ;			
#endif	
}

bool PlayerNameWnd::canDrag (int tx, int ty)
{
	return true ;
}

void PlayerNameWnd::onCommand (int id)
{
}




/*
void PlayerStatusWnd::draw (HDC hdc)
{
	Window::draw (hdc, 0, 0) ;
	char buf[256] ;
	sprintf_s (buf, sizeof(buf), "hp:%d", pUnitData->hp) ;
	TextOut (hdc, x+2, y+2, buf, strlen (buf)) ;
	sprintf_s (buf, sizeof(buf), "mp:%d", pUnitData->mp) ;
	TextOut (hdc, x+2, y+2+20, buf, strlen (buf)) ;
}
*/
