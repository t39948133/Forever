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
	overlayUI.init (x, y, w, h) ;

	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayUI, 0, 0, w, h, 0) ;
	pBtn->setImage ("elyos") ;
	addChild (pBtn) ;

	TextArea* pTA = new TextArea ;
	pTA->init (overlayUI, 2, 80, CELL_W, 20) ;
	char buf[64] ;
	sprintf (buf, "LV :  %d", pUnitData->m_level) ;
	pTA->setText (buf, 1, 1, 1) ;
	addChild (pTA) ;
	

#else _PROJECT_GDI_
	TextButton* pBtn = new TextButton ;
	pBtn->init (0, 0, w, h, 0) ;
	pBtn->str = "ª±®aÀY¹³" ;
	addChild (pBtn) ;

	TextArea* pTA = new TextArea ;
	pTA->init (2, 80, CELL_W, 20) ;
	char buf[64] ;
	sprintf_s (buf, sizeof (buf), "LV :  %d", pUnitData->m_level) ;
	pTA->setText (buf, 1, 1, 1) ;
	addChild (pTA) ;
	
#endif
	
}

bool PlayerImageWnd::canDrag (int tx, int ty)
{
	return false ;
}

void PlayerImageWnd::onCommand (int id)
{
}

#ifdef _PROJECT_OGRE_3D_
void PlayerImageWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void PlayerImageWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void PlayerImageWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif
