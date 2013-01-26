#include "mini_map_wnd.h"
const float MATH_PI = 3.141592f ;
void MiniMapWnd::init (int _x, int _y, Unit* _pPlr, Scene* _pScene, float* _camDir)
{
	pPlr = _pPlr ;
	x = _x ;
	y = _y ;
	w = HALF_MAP_SIZE*2 ;
	h = HALF_MAP_SIZE*2;	
	pScene = _pScene ;
	camDir = _camDir ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("minimap") ;
#endif

#ifdef _PROJECT_OGRE_3D_
	//主角
	pBtn = new ImageButton ;
	pBtn->init (overlayUI, HALF_MAP_SIZE, HALF_MAP_SIZE, ICON_SIZE, ICON_SIZE, 0) ;
	pBtn->setImage ("droplet") ;
	addChild (pBtn) ;

/*
	pText = new TextArea ;
	pText->init (overlayUI, 0, 0, 100, 30) ;
	pText->setText ("小地圖", 1, 1, 1) ;
	addChild (pText) ;*/

#endif

}

void MiniMapWnd::update()
{
#ifdef _PROJECT_OGRE_3D_
	V_MINI_ICON::iterator pi = vMiniIcon.begin () ;
	while (pi != vMiniIcon.end ())
	{
		//更新button的位置
		//pi->x = pi->pUnit->x ;
		//pi->y = pi->pUnit->y ;
		float dx = (pPlr->x - pi->pUnit->x)/10 ;
		float dy = (pPlr->y - pi->pUnit->y)/10 ;
		dx = -dx * cos(*camDir+MATH_PI/2) ;
		dy = dy * sin(*camDir+MATH_PI/2) ;
		if(pi->pUnit != NULL)
		{
			pi->getImage()->setPosition(dx + HALF_MAP_SIZE, dy + HALF_MAP_SIZE) ;
			//pi->getImage()->setPosition(pi->pUnit->x, pi->pUnit->y) ;
		}

		++ pi ;
	}
#endif
}

void MiniMapWnd::onAddUnit (Unit* pu)
{
#ifdef _PROJECT_OGRE_3D_
	MiniIcon icon ;	
	icon.pUnit = pu ;
	vMiniIcon.push_back (icon) ;

	vMiniIcon.back ().init(overlayUI, pu->x, pu->y, 6, 6, vMiniIcon.size()) ;
	vMiniIcon.back ().setImage ("GLX_icon") ;

	//ImageButton* pib = new ImageButton ;
	//pib->init(overlay, mx, my, 10, 10, t) ;
	addChild(&(vMiniIcon.back ())) ;
#endif

}

void MiniMapWnd::onDelUnit (Unit* pu)
{
#ifdef _PROJECT_OGRE_3D_
	V_MINI_ICON::iterator pi = vMiniIcon.begin () ;
	while (pi != vMiniIcon.end ())
	{
		if (pi->pUnit == pu)
		{
			delChild (&(*pi)) ;
			vMiniIcon.erase (pi) ;
			break ;

		}

		++ pi ;
	}
#endif
}


bool MiniMapWnd::canDrag (int tx, int ty)
{
	return false ;
}

void MiniMapWnd::onMove ()
{
#ifdef _PROJECT_OGRE_3D_
	overlayUI.setPos (x, y) ;
#endif
}

void MiniMapWnd::setZOrder (int z)
{
#ifdef _PROJECT_OGRE_3D_
	overlayUI.setZOrder (z) ;
#endif
}

void MiniMapWnd::show (bool bs)
{
	Window::show (bs) ;
#ifdef _PROJECT_OGRE_3D_
	overlayUI.show (bs) ;
#endif
}