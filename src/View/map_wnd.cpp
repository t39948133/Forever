#include "map_wnd.h"
#include "image_button.h"

void MapWnd::init (int _x, int _y)
{
	x = _x ;
	y = _y ;
	w = CELL_SIZE*CELL_W_COUNT ;
	h = CELL_SIZE*CELL_H_COUNT ;

#ifdef _PROJECT_OGRE_3D_
/*		overlay.init (x, y, w, h) ;
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


