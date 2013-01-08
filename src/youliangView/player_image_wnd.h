#ifndef _PLAYER_IMAGE_WND_H_
#define _PLAYER_IMAGE_WND_H_

#include "window.h"
#include "unit.h"

class PlayerImageWnd:public Window
{
private:
	UnitData* pUnitData ;

public:
	enum {CELL_W = 70, CELL_H = 100} ;

	~PlayerImageWnd () {};

	void init (int _x, int _y, UnitData* pu) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int id) ;

#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
	void onSwitch () ;
#endif

//	void draw (HDC hdc) ;
} ;


#endif