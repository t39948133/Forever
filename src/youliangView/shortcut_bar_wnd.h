#ifndef _SHORTCUT_BAR_WND_H_
#define _SHORTCUT_BAR_WND_H_

#include "window.h"
#include "unit.h"
class ShortcutBarWnd:public Window
{
private:
	UnitData* pUnitData ;

public:
	enum {CELL_W_COUNT = 10, CELL_SIZE = 40} ;

	~ShortcutBarWnd () {};

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