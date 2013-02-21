#include "CMapWnd.h"

void CMapWnd::init (int _x, int _y)
{
	x = _x ;
	y = _y ;
	w = CELL_SIZE ;
	h = CELL_SIZE ;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
    m_overlay.setBackImage("map");
	
#endif
	show(false);			
}

bool CMapWnd::canDrag (int tx, int ty)
{
	return false ;
}

void CMapWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

#ifdef _GAMEENGINE_3D_
void CMapWnd::onDrag()
{
   m_overlay.setPosition(x, y);
}

void CMapWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_


