#include "skill_info_wnd.h"
#include "overlayUI.h"
#include "image_button.h"


void SkillInfoWnd::init (int _x, int _y)
{
	bVisible = false ;
	x = _x ;
	y = _y ;
	w = 400 ;
	h = 80 ;
#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.show (false) ;
	overlayUI.setImage ("infownd") ;
#endif

	vpText[0] = new TextArea ;
#ifdef _PROJECT_OGRE_3D_
	vpText[0]->init (overlayUI, 5, 5, w, h) ;
#else _PROJECT_GDI_
	vpText[0]->init (5, 5, w, h) ;
#endif
	addChild (vpText[0]) ;
}

void SkillInfoWnd::setItem (const char* ps)
{
	vpText[0]->setText (ps, 1, 1, 1) ;
}

void SkillInfoWnd::setPos (int _x, int _y)
{
	x = _x ;
	y = _y ;
#ifdef _PROJECT_OGRE_3D_
	overlayUI.setPos (_x, _y) ;
#endif
}

void SkillInfoWnd::show (bool bs)
{
	Window::show (bs) ;
#ifdef _PROJECT_OGRE_3D_
	overlayUI.show (bs) ;
#endif
}

void SkillInfoWnd::draw (HDC hdc, int ox, int oy)
{
	Window::draw (hdc, ox, oy) ;
//	TextOut (hdc, x+ox+2, y+oy+2, str, str.length ()) ;
}