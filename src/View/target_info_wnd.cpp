#include "target_info_wnd.h"
#include "scene.h"

	void TargetInfoWnd::init (Scene* pscn, float tx, float ty)
	{
		pScene = pscn ;
		x = int(tx) ;
		y = int(ty) ;
		w = 150 ;
		h = 50 ;
		targetUID = -1 ;
	}

	Unit* TargetInfoWnd::getTarget ()
	{
		return pScene->getUnit (targetUID) ;
	}

	bool TargetInfoWnd::canDrag (int tx, int ty)
	{
		return false ;
	}

	void TargetInfoWnd::setTarget (long long id)
	{
		targetUID = id ;
	}

	void TargetInfoWnd::draw (HDC hdc)
	{
		Window::draw (hdc, 0, 0) ;

		Unit* pU = pScene->getUnit (targetUID) ;

		if (pU != NULL)
		{
			char buf[256] ;
			sprintf_s (buf, sizeof(buf), "hp:%d", pU->data.hp) ;
			TextOut (hdc, x+2, y+2, buf, strlen (buf)) ;
		}
	}
