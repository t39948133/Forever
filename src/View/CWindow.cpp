#include "CWindow.h"

CWindow::CWindow() : pParent(NULL),
                     x(0),
                     y(0),
                     w(0),
                     h(0),
                     bVisible(true)
{
}

CWindow::~CWindow()
{
   pParent = NULL;
}

bool CWindow::checkPoint(int tx, int ty)
{
	if (bVisible == false)
		return false ;

	if ((tx >= x) && (tx < (x+w)) &&
		(ty >= y) && (ty < (y+h)))
		return true ;
	else
		return false ;
}

void CWindow::addChild(CWindow* pw)
{
	pw->pParent = this ;
	vpWnd.push_back (pw) ;
}

bool CWindow::canDrag(int tx, int ty)
{
	return true ;
}

void CWindow::onLClick(int tx, int ty)
{
	tx -= x ;
	ty -= y ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			if ((*pi)->checkPoint (tx, ty))
			{
				(*pi)->onLClick (tx, ty) ;
				break ;
			}

		++ pi ;
	}

	if (pi == vpWnd.end ())
	{
		//沒按到子視窗
	}
}

void CWindow::onRClick(int tx, int ty)
{
   tx -= x ;
	ty -= y ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			if ((*pi)->checkPoint (tx, ty))
			{
				(*pi)->onRClick (tx, ty) ;
				break ;
			}

		++ pi ;
	}

	if (pi == vpWnd.end ())
	{
		//沒按到子視窗
	}
}

WindowClassType CWindow::getClassType()
{
   return WND_NULL;
}

#ifdef _GAMEENGINE_2D_
void CWindow::draw(HDC hdc, int ox, int oy)
{
	Rectangle (hdc, x+ox, y+oy, x+ox+w, y+oy+h) ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			(*pi)->draw (hdc, x+ox, y+oy) ;
		++ pi ;
	}
}
#endif

