#include "target_info_wnd.h"
#include "scene.h"
#include "image_button.h"

void TargetInfoWnd::init (Scene* pscn, float tx, float ty)
{
	pScene = pscn ;
	x = int(tx) ;
	y = int(ty) ;
	w = 300 ;
	h = 60 ;
	targetUID = -1 ;


#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;

	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayUI, 50, 15, 200, 15, 0) ;
	pBtn->setImage ("ogreborder") ;
	addChild (pBtn) ;

	TextArea* pTA = new TextArea ;
	pTA->init (overlayUI, 50, 35, w, h) ;
	pTA->setText ("¥vµÜ©i", 1, 1, 1) ;
	addChild (pTA) ;
	
#else _PROJECT_GDI_
	TextButton* pBtn = new TextButton ;
	pBtn->init (50, 15, 200, 15, 0) ;
	addChild (pBtn) ;
	
	TextArea* pTA = new TextArea ;
	pTA->init (50, 35, w, h) ;
	pTA->setText ("¥vµÜ©i", 1, 1, 1) ;
	addChild (pTA) ;

#endif
}

Unit* TargetInfoWnd::getTarget ()
{
	return pScene->getUnit (targetUID) ;
}

bool TargetInfoWnd::canDrag (int tx, int ty)
{
	return false ;
}

void TargetInfoWnd::setTarget (long long id)
{
	targetUID = id ;
}

void TargetInfoWnd::onCommand (int id)
{
}

#ifdef _PROJECT_OGRE_3D_
void TargetInfoWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void TargetInfoWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void TargetInfoWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

/*
void TargetInfoWnd::draw (HDC hdc)
{
	Window::draw (hdc, 0, 0) ;

	Unit* pU = pScene->getUnit (targetUID) ;

	if (pU != NULL)
	{
		char buf[256] ;
		sprintf_s (buf, sizeof(buf), "hp:%d", pU->data.hp) ;
		TextOut (hdc, x+2, y+2, buf, strlen (buf)) ;
	}
}
*/
