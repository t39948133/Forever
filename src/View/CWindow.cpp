#include "CWindow.h"

CWindow::CWindow() : pParent(NULL),
                     x(0),
                     y(0),
                     w(0),
                     h(0),
                     m_bVisible(true),
                     m_pWindowMan(NULL)
{
}

CWindow::~CWindow()
{
   pParent = NULL;
}

bool CWindow::checkPoint(int tx, int ty)
{
	if(m_bVisible == false)
		return false;

	if ((tx >= x) && (tx < (x+w)) &&
		(ty >= y) && (ty < (y+h)))
		return true ;
	else
		return false ;
}

void CWindow::addChild(CWindow* pChildWnd)
{
	pChildWnd->pParent = this;
	vpWnd.push_back(pChildWnd);
}

bool CWindow::canDrag(int tx, int ty)
{
	return true ;
}

void CWindow::onDrag()
{
}

void CWindow::onLClick(int tx, int ty)
{
	tx -= x ;
	ty -= y ;

	VP_WND::iterator pi = vpWnd.begin();
	while (pi != vpWnd.end ())
	{
		if ((*pi)->m_bVisible)
			if ((*pi)->checkPoint(tx, ty))
			{
				(*pi)->onLClick(tx, ty);
				break;
			}

		++ pi;
	}

	if (pi == vpWnd.end ())
	{
		//沒按到子視窗
	}
}

void CWindow::onRClick(int tx, int ty)
{
   tx -= x;
	ty -= y;

	VP_WND::iterator pi = vpWnd.begin();
	while(pi != vpWnd.end())
	{
		if((*pi)->m_bVisible)
			if((*pi)->checkPoint(tx, ty))
			{
				(*pi)->onRClick(tx, ty);
				break;
			}

		++pi;
	}

	if(pi == vpWnd.end())
	{
		//沒按到子視窗
	}
}

void CWindow::onLCommand(int btnID)
{
}

void CWindow::onRCommand(int btnID)
{
}

WindowClassType CWindow::getClassType()
{
   return WND_NULL;
}

void CWindow::setWindowMan(CWindowMan *pWndMan)
{
   m_pWindowMan = pWndMan;
}

bool CWindow::isVisible()
{
   return m_bVisible;
}

void CWindow::show(bool bShow)
{
   m_bVisible = bShow;
}

#ifdef _GAMEENGINE_3D_
void CWindow::setZOrder(int order)
{
}
#elif _GAMEENGINE_2D_
void CWindow::draw(HDC hdc, int ox, int oy)
{
	Rectangle (hdc, x+ox, y+oy, x+ox+w, y+oy+h) ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->m_bVisible)
			(*pi)->draw (hdc, x+ox, y+oy) ;
		++ pi ;
	}
}
#endif

CWindowMan* CWindow::getWindowMan()
{
   return m_pWindowMan;
}