#include "CToolBarWnd.h"

#ifdef _GAMEENGINE_3D_
#include <OgreTextAreaOverlayElement.h>
#endif  // #ifdef _GAMEENGINE_3D_

CToolBarWnd::CToolBarWnd()
{
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++) {
      m_vpTextName[i] = NULL;
      m_vpText[i] = NULL;
   }
}

CToolBarWnd::~CToolBarWnd()
{
   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }
   }

   for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_vpTextName[i] != NULL) {
         delete m_vpTextName[i];
         m_vpTextName[i] = NULL;
      }

      if(m_vpText[i] != NULL) {
         delete m_vpText[i];
         m_vpText[i] = NULL;
      }
   }
}

void CToolBarWnd::init (CWindow* pw0,  CWindow* pw1, CWindow* pw2, CWindow* pw3,
					   int _x, int _y)
{
	vpWnd[0] = pw0 ;
	vpWnd[1] = pw1 ;
	vpWnd[2] = pw2 ;
	vpWnd[3] = pw3 ;

	x = _x ;
	y = _y ;
	w = 250 ;
	h = 60 ;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
	m_overlay.setBackImage("UI/BG/ToolBarWnd");
   m_overlay.setZOrder(20);

	for (int i = 0; i<BUTTON_COUNT; i++){
		m_vpBtn[i] = new CImageButton() ;
		m_vpBtn[i]->init (&m_overlay, (i*41)+50, 17, ICON_SIZE, ICON_SIZE, i) ;
		addChild (m_vpBtn[i]) ;
	}
#elif _GAMEENGINE_2D_
	
	for (int i = 0; i<BUTTON_COUNT; i++){
		m_vpBtn[i] = new CTextButton();
		m_vpBtn[i]->init (i*ICON_SIZE, 0, ICON_SIZE, ICON_SIZE, i) ;
		if (i == 0)
			m_vpBtn[i]->str = "背包" ;
		else if (i == 1)
			m_vpBtn[i]->str = "主角" ;
		else if (i == 2)
			m_vpBtn[i]->str = "技能" ;
		else if (i == 3)
			m_vpBtn[i]->str = "地圖" ;
		addChild (pBtn) ;		
	}	

#endif
}

bool CToolBarWnd::canDrag (int tx, int ty)
{
	return false ;
}

void CToolBarWnd::onLCommand (int btnID)
{
	vpWnd[btnID]->show (!vpWnd[btnID]->isVisible ()) ;
}

void CToolBarWnd::onDrag()
{   
#ifdef _GAMEENGINE_3D_
   m_overlay.setPosition(x, y);
#endif  // #ifdef _GAMEENGINE_3D_
}

/*
void CPlayerInfoWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

*/
