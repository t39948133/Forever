#include "CMiniMapWnd.h"
const float MATH_PI = 3.141592f ;

void CMiniMapWnd::init (int _x, int _y, CUnitObject* _pPlr, CScene* _pScene, float* _camDir)
{
	pPlr = _pPlr ;
	x = _x ;
	y = _y ;
	w = HALF_MAP_SIZE*2 ;
	h = HALF_MAP_SIZE*2;	
	pScene = _pScene ;
	camDir = _camDir ;

#ifdef _GAMEENGINE_3D_
	m_overlay.init (x, y, w, h) ;
	m_overlay.setBackImage ("minimap2") ;
#endif

#ifdef _GAMEENGINE_3D_
	//主角
	pBtn = new CImageButton ;
	pBtn->init (&m_overlay, HALF_MAP_SIZE, HALF_MAP_SIZE, ICON_SIZE*2, ICON_SIZE*2, 0) ;
	pBtn->setImage ("droplet") ;
	addChild (pBtn) ;

	pText = new CTextAreaOgre ;
	pText->init (&m_overlay, 5, 20, 100, 30) ;
	pText->setText ("雷達", 1, 0.8, 1) ;
	addChild (pText) ;

#endif

}

void CMiniMapWnd::update()
{
#ifdef _GAMEENGINE_3D_
	V_MINI_ICON::iterator pi = vMiniIcon.begin () ;
	while (pi != vMiniIcon.end ())
	{
		//更新button的位置
		//pi->x = pi->pUnit->x ;
		//pi->y = pi->pUnit->y ;
		float dx = (pPlr->getPosition().fX - pi->pUnit->getPosition().fX)/5 ;
		float dy = (pPlr->getPosition().fY - pi->pUnit->getPosition().fY)/5 ;
//		dx = -dx * cos(*camDir+MATH_PI/2) ;
//		dy = dy * sin(*camDir+MATH_PI/2) ;
		if(pi->pUnit != NULL)
		{
			pi->getImage()->setPosition(-dx + HALF_MAP_SIZE,-dy + HALF_MAP_SIZE) ;
		}

		++ pi ;
	}
#endif
}

void CMiniMapWnd::onAddUnit (CUnitObject* pu)
{
#ifdef _GAMEENGINE_3D_
	CMiniIcon icon ;	
	icon.pUnit = pu ;
	vMiniIcon.push_back (icon) ;

	vMiniIcon.back ().init(&m_overlay, pu->getPosition().fX, pu->getPosition().fY, 
		ICON_SIZE, ICON_SIZE, vMiniIcon.size()) ;

	vMiniIcon.back ().setImage ("GLX_icon") ;

	//ImageButton* pib = new ImageButton ;
	//pib->init(overlay, mx, my, 10, 10, t) ;
	addChild(&(vMiniIcon.back ())) ;
#endif
}

void CMiniMapWnd::onAddNPCUnit (CUnitObject* pu)
{
#ifdef _GAMEENGINE_3D_
	CMiniIcon icon ;	
	icon.pUnit = pu ;
	vMiniIcon.push_back (icon) ;

	vMiniIcon.back ().init(&m_overlay, pu->getPosition().fX, pu->getPosition().fY, 
		ICON_SIZE, ICON_SIZE, vMiniIcon.size()) ;

	vMiniIcon.back ().setImage ("tusk") ;

	//ImageButton* pib = new ImageButton ;
	//pib->init(overlay, mx, my, 10, 10, t) ;
	addChild(&(vMiniIcon.back ())) ;
#endif
}

void CMiniMapWnd::onDelUnit (CUnitObject* pu)
{
#ifdef _GAMEENGINE_3D_
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


bool CMiniMapWnd::canDrag (int tx, int ty)
{
	return false ;
}

void CMiniMapWnd::onDrag ()
{
#ifdef _GAMEENGINE_3D_
	m_overlay.setPosition(x, y);
#endif
}

void CMiniMapWnd::setZOrder (int order)
{
#ifdef _GAMEENGINE_3D_
	m_overlay.setZOrder(order);
#endif
}

void CMiniMapWnd::show (bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}