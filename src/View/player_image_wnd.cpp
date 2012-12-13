#include "player_image_wnd.h"
#include "image_button.h"


void PlayerImageWnd::init (int _x, int _y, UnitData* pu)
{
	pUnitData = pu ;
	x = _x ;
	y = _y ;
	w = CELL_W ;
	h = CELL_H ;

#ifdef _PROJECT_OGRE_3D_
		overlayPIM.init (x, y, w, h) ;
#endif

		
#ifdef _PROJECT_GDI_
			TextButton* pBtn = new TextButton ;

			pBtn->init (0, 0, w, h, 0) ;

			if (i == 0)
				pBtn->str = "ª±®aÀY¹³" ;
		
#else _PROJECT_OGRE_3D_
			ImageButton* pBtn = new ImageButton ;

			pBtn->init (overlayPIM, 0, 0, w, h, 0) ;
			pBtn->setImage ("elyos") ;

#endif
			addChild (pBtn) ;
}

bool PlayerImageWnd::canDrag (int tx, int ty)
{
	return true ;
}

void PlayerImageWnd::onCommand (int id)
{
}

#ifdef _PROJECT_OGRE_3D_
void PlayerImageWnd::onMove ()
{
	overlayPIM.setPos (x, y) ;
}

void PlayerImageWnd::setZOrder (int z)
{
	overlayPIM.setZOrder (z) ;
}
#endif
