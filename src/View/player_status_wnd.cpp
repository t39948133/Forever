#include "player_status_wnd.h"
#include "image_button.h"

void PlayerStatusWnd::init (int _x, int _y, UnitData* pu)
{
	pUnitData = pu ;

	x = _x ;
	y = _y ;

	w = CELL_W ;
	h = CELL_H*BUTTON_COUNT ;

#ifdef _PROJECT_OGRE_3D_
	overlayPS.init (x, y, w, h) ;

	for (int i = 0; i<BUTTON_COUNT; i++)
	{		
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlayPS, 0, i*CELL_H, CELL_W, CELL_H, i) ;
		if (i == 0)
		{
			pBtn->setImage ("ogreborder") ;
		}else if (i == 0)
		{
			pBtn->setImage ("ogreborder") ;
		}else 
		{
			pBtn->setImage ("ogreborder") ;
		}
		
		addChild (pBtn) ;
	}
/*
	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayPS, w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 24) ;
	//pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
//		char buf[256] ;

		pTA->init (overlayPS, -20, i*CELL_H, CELL_W, CELL_H) ;
		if (i == 0)
		{	
			pTA->setText ("HP", 1, 1, 1) ;
		}else if (i == 1)
		{
			pTA->setText ("MP", 1, 1, 1) ;
		}else
		{
			pTA->setText ("XP", 1, 1, 1) ;
		}

		addChild (pTA) ;
	}
#else _PROJECT_GDI_
	for (int i = 0; i<CELL_H_COUNT; i++)
	{
		TextButton* pBtn = new TextButton ;

		pBtn->init (-20, i*CELL_H, CELL_W, CELL_H, i) ;

		if (i == 0)
			pBtn->str = "hp" ;
		else if (i == 1)
			pBtn->str = "mp" ;
		else if (i == 2)
			pBtn->str = "exp" ;

		addChild (pBtn) ;
	}
#endif
}

bool PlayerStatusWnd::canDrag (int tx, int ty)
{
	return true ;
}

void PlayerStatusWnd::onCommand (int id)
{

}

#ifdef _PROJECT_OGRE_3D_
void PlayerStatusWnd::onMove ()
{
	overlayPS.setPos (x, y) ;
}

void PlayerStatusWnd::setZOrder (int z)
{
	overlayPS.setZOrder (z) ;
}
#endif

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
