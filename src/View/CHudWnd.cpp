#ifdef _GAMEENGINE_3D_
#include "CHudWnd.h"

CHudWnd::CHudWnd() : m_pPlayer(NULL)
{
}

void CHudWnd::init(int _x, int _y, CPlayer *pPlayer)
{
   m_pPlayer = pPlayer;
   x = _x;
   y = _y;
   w = 856;
   h = 126;

   m_overlay.init(x, y, w, h);
   m_overlay.setBackImage("UI/BG/HudWnd");
   m_overlay.setZOrder(20);
   show(true);
}

bool CHudWnd::canDrag(int tx, int ty)
{
	return false;
}

WindowClassType CHudWnd::getClassType()
{
   return WND_HUD;
}

void CHudWnd::show(bool bShow)
{
   CWindow::show(bShow);

   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
}

int CHudWnd::getZOrder()
{
   return m_overlay.getZOrder();
}
#endif  // #ifdef _GAMEENGINE_3D_