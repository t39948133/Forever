#include "map_wnd.h"
#include "image_button.h"

void MapWnd::init (int _x, int _y)
{
	bVisible = false ;
	x = _x ;
	y = _y ;
	w = CELL_SIZE*CELL_W_COUNT ;
	h = CELL_SIZE*CELL_H_COUNT ;

#ifdef _PROJECT_OGRE_3D_
		overlayUI.init (x, y, w, h) ;
		overlayUI.getOverlay ()->hide () ;

		pBtn = new ImageButton ;
		pBtn->init (overlayUI, 0, 0, w, h, 0) ;
		pBtn->setImage ("map") ;
		addChild (pBtn) ;

#else _PROJECT_GDI_
		pBtn = new TextButton ;

		pBtn->init (0, 0, w, h, 0) ;

		pBtn->str = "¦a¹Ï" ;

		addChild (pBtn) ;			
#endif
			
}

bool MapWnd::canDrag (int tx, int ty)
{
	return true ;
}

void MapWnd::onCommand (int id)
{
}

#ifdef _PROJECT_OGRE_3D_
void MapWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void MapWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}
void MapWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

