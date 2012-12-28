#include "shortcut_bar_wnd.h"
#include "image_button.h"

void ShortcutBarWnd::init (int _x, int _y, UnitData* pu)
{
	pUnitData = pu ;
	x = _x ;
	y = _y ;
	w = CELL_W_COUNT*CELL_SIZE ;
	h = CELL_SIZE ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;

	for (int i = 0; i<CELL_W_COUNT; i++)
	{
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlayUI, (i)*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;

		
		if (i == 0)
			pBtn->setImage ("skill_2") ;
		else if (i == 1)
			pBtn->setImage ("skill_3") ;
		else if (i == 2)
			pBtn->setImage ("skill_4") ;
		else if (i == 3)
			pBtn->setImage ("skill_5") ;
		else
			pBtn->setImage ("ogreborder") ;
		
		addChild (pBtn) ;
	}

#else _PROJECT_GDI_
	for (int i = 0; i<CELL_W_COUNT; i++)
	{
		TextButton* pBtn = new TextButton ;

		pBtn->init (i*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;

		if (i == 0)
			pBtn->str = "§Ö" ;
		else if (i == 1)
			pBtn->str = "±¶" ;
		else if (i == 2)
			pBtn->str = "¦C" ;
		else
			pBtn->str = "" ;
	
		addChild (pBtn) ;
	}
#endif
}

bool ShortcutBarWnd::canDrag (int tx, int ty)
{
	return true ;
}

void ShortcutBarWnd::onCommand (int id)
{
}
#ifdef _PROJECT_OGRE_3D_
void ShortcutBarWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void ShortcutBarWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}
#endif





