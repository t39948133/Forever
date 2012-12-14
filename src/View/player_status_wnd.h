#ifndef _PLAYER_STATUS_WND_H_
#define _PLAYER_STATUS_WND_H_

#include "window.h"
#include "unit.h"
#ifdef _PROJECT_OGRE_3D_
	#include "overlayUI.h"
#endif

class PlayerStatusWnd:public Window
{
private:
	UnitData* pUnitData ;
	enum {BUTTON_COUNT = 3, CELL_W = 200, CELL_H = 15, TEXT_COUNT = 3} ;
	
	#ifdef _PROJECT_OGRE_3D_
		OverlayUI overlayPS ;//ºÞ²zoverlay
	#endif

public:
	~PlayerStatusWnd () {};

	void init (int _x, int _y, UnitData* pu) ;
	
	bool canDrag (int tx, int ty) ;

	void onCommand (int) ;

#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
#endif

//	void draw (HDC hdc) ;
} ;


#endif