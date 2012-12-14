#ifndef _MINI_MAP_WND_H_
#define _MINI_MAP_WND_H_

#include "window.h"
#include "unit.h"

class MiniMapWnd:public Window
{
private:
	UnitData* pUnitData ;

public:
	enum {CELL_H_COUNT = 1, CELL_W_COUNT = 1,CELL_SIZE = 100} ;

	~MiniMapWnd () {};

	void init (int _x, int _y, UnitData* pu) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int id) ;

//	void draw (HDC hdc) ;
} ;


#endif