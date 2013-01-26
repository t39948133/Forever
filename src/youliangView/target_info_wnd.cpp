#include "target_info_wnd.h"
#include "scene.h"
#include "image_button.h"

void TargetInfoWnd::init (Scene* pscn, float tx, float ty)
{
	pScene = pscn ;
	x = int(tx) ;
	y = int(ty) ;
	w = 300 ;
	h = 74 ;
	targetUID = -1 ;


#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("target") ;

	vpBtn[0] = new ImageButton ;
	vpBtn[0]->init (overlayUI, 63, 31, 190, 9, 0) ;
	vpBtn[0]->setImage ("hp") ;
	addChild (vpBtn[0]) ;

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		if (i == 0)
		{
			vpText[i]->init (overlayUI, 100, 55, 200, 20) ;
		}else
		{
			vpText[i]->init (overlayUI, 10, 29, 20, 20) ;
			vpText[i]->setText ("1", 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
	
#else _PROJECT_GDI_
	vpBtn[0] = new TextButton ;
	vpBtn[0]->init (50, 15, 200, 15, 0) ;
	addChild (vpBtn[0]) ;

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		if (i == 0)
		{
			vpText[i]->init (50, 35, 200, 20) ;
		}else
		{
			vpText[i]->init (10, 29, 20, 20) ;
			vpText[i]->setText ("1", 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
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

	Monster* pm = pScene->getMonster (targetUID) ;
	vpText[0]->setText (pm->getInfo()->name, 1, 1, 1) ;
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
