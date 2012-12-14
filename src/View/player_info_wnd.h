#ifndef _PLAYER_INFO_WND_H_
#define _PLAYER_INFO_WND_H_

#include "window.h"
#include "unit.h"
#ifdef _PROJECT_OGRE_3D_
	#include "overlayUI.h"
#endif

class PlayerInfoWnd:public Window
{
private:
	UnitData* pUnitData ;
	TextArea* pTA ;
#ifdef _PROJECT_OGRE_3D_
	OverlayUI overlayPIN ;//ºÞ²zoverlay
#endif

public:
	enum {BUTTON_COUNT = 13, CELL_SIZE = 20, TEXT_COUNT = 21} ;

	~PlayerInfoWnd () {};

	void init (int _x, int _y, UnitData* pu) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int id) ;

#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
#endif

//	void draw (HDC hdc) ;
} ;


#endif