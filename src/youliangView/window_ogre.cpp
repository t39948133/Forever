#ifdef _PROJECT_OGRE_3D_

#include "window_ogre.h"


void WindowManOgre::init ()
{
	cursorUI.init (0, 0, 40, 40) ;
	cursorUI.setZOrder (100) ;
	cursorUI.setImage ("cursor") ;
}

bool WindowManOgre::work (HWND hWnd, KeyMan& keyMan)
{
	bool r = WindowMan::work (hWnd, keyMan) ;

	cursorUI.setPos (clientX, clientY) ;

	int offset = 0 ; 
	VP_WINDOW::iterator pi = vpWindow.begin () ;
	while (pi != vpWindow.end ())
	{
		(*pi)->setZOrder (100-offset-1) ;
		offset ++ ;
		++ pi ;
	}

	return r ;
}
#endif
