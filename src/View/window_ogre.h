#ifndef _WINDOW_OGRE_H_
#define _WINDOW_OGRE_H_

#ifdef _PROJECT_OGRE_3D_

#include "window.h"
#include "overlayUI.h"

class WindowManOgre:public WindowMan
{
private:
	OverlayUI cursorUI ;//ЙCМа

public:
	void init () ;
	bool work (HWND hWnd, KeyMan&) ;
} ;

#endif

#endif
