#ifndef _BACKPACK_WND_H_
#define _BACKPACK_WND_H_

#include "window.h"
#include "player.h"

#ifdef _PROJECT_OGRE_3D_
	#include "overlayUI.h"
#endif

//背包視窗

class BackpackWnd:public Window
{
public:
//	Backpack* pBackpack ;
	enum {BUTTON_COUNT = 25, CELL_SIZE = 60, TEXT_COUNT = 26} ;
	Player* pPlayer ;
	#ifdef _PROJECT_OGRE_3D_
		OverlayUI overlayBP ;//管理overlay
	#endif

	~BackpackWnd () {};

	void init (int _x, int _y, Player* pb) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int) ;
#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;

#endif
//	void onClick (int tx, int ty) ;

//	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif