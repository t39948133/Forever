#include "CSkillInfoWnd.h"

CSkillInfoWnd::CSkillInfoWnd ()
{
	for (int i = 0; i<TEXT_COUNT; i++)
		m_vpText[i] = NULL ;
}

CSkillInfoWnd::~CSkillInfoWnd ()
{
	for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_vpText[i] != NULL) {
         delete m_vpText[i];
         m_vpText[i] = NULL;
	  }
	}
}

void CSkillInfoWnd::init (int _x, int _y)
{
	CWindow::show(false)  ;
	x = _x ;
	y = _y ;
	w = 400 ;
	h = 60 ;
#ifdef _GAMEENGINE_3D_
	m_overlay.init (x, y, w, h) ;
//	m_overlay.show (false) ;
	m_overlay.setBackImage ("infownd") ;
#endif

	
#ifdef _GAMEENGINE_3D_
	m_vpText[0] = new CTextAreaOgre() ;
	m_vpText[0]->init (&m_overlay, 0, 0, w, h) ;
#else _GAMEENGINE_2D_
	m_vpText[0] = new CTextArea() ;
	m_vpText[0]->init (0, 0, w, h) ;
#endif
	addChild (m_vpText[0]) ;
}

void CSkillInfoWnd::setItem (std::string ps)
{
	m_vpText[0]->setText (ps, 1, 1, 1) ;
}

void CSkillInfoWnd::setPos (int _x, int _y)
{
	x = _x ;
	y = _y ;
#ifdef _GAMEENGINE_3D_
	m_overlay.setPosition (_x, _y) ;
#endif
}

void CSkillInfoWnd::show (bool bs)
{
	CWindow::show (bs) ;
#ifdef _GAMEENGINE_3D_
//	m_overlay.show (bs) ;
#endif
}

void CSkillInfoWnd::draw (HDC hdc, int ox, int oy)
{
#ifdef _GAMEENGINE_2D_
	CWindow::draw (hdc, ox, oy) ;
#endif
}

void CSkillInfoWnd::setZOrder(int order)
{
#ifdef _GAMEENGINE_3D_
	m_overlay.setZOrder(order);
#endif  // #ifdef _GAMEENGINE_3D_
}