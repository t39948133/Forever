#include "player_image_wnd.h"
#include "image_button.h"


void PlayerImageWnd::init (int _x, int _y, UnitData* pu)
{
	pUnitData = pu ;
	x = _x ;
	y = _y ;
#ifdef _PROJECT_OGRE_3D_
	w = 700 ;
#else _PROJECT_GDI_
	w = 104 ;
#endif
	h = 104 ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("player_hotkey") ;

	pBtn = new ImageButton ;
	pBtn->init (overlayUI, 0, 0, w, h, 0) ;
//	pBtn->setImage ("") ;
	addChild (pBtn) ;

	pText = new TextArea ;
	pText->init (overlayUI, 90, 81, 20, 20) ;
	char buf[64] ;
	sprintf (buf, "%d", pUnitData->m_level) ;
	pText->setText (buf, 1, 1, 1) ;
	addChild (pText) ;
	

#else _PROJECT_GDI_
	pBtn = new TextButton ;
	pBtn->init (0, 0, 80, 20, 0) ;
	pBtn->str = "ª±®aÀY¹³" ;
	addChild (pBtn) ;

	pText = new TextArea ;
	pText->init (2, 80, 20, 20) ;
	char buf[64] ;
	sprintf_s (buf, sizeof (buf), "LV :  %d", pUnitData->m_level) ;
	pText->setText (buf, 1, 1, 1) ;
	addChild (pText) ;
	
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
