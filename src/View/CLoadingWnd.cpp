#ifdef _GAMEENGINE_3D_
#include "CLoadingWnd.h"

CLoadingWnd::CLoadingWnd()
{
}

void CLoadingWnd::init(int _x, int _y, int width, int height)
{
   x = _x;
   y = _y;
   w = width;
   h = height;

   m_overlay.init(x, y, w, h);
   m_overlay.setBackImage("UI/BG/Loading");
   m_overlay.setZOrder(649);
   show(false);
}

bool CLoadingWnd::canDrag(int tx, int ty)
{
	return false;
}

WindowClassType CLoadingWnd::getClassType()
{
   return WND_LOADING;
}

void CLoadingWnd::show(bool bShow)
{
   CWindow::show(bShow);

   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
}

int CLoadingWnd::getZOrder()
{
   return m_overlay.getZOrder();
}
#endif  // #ifdef _GAMEENGINE_3D_