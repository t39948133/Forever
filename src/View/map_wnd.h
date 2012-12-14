#ifndef _MAP_WND_H_
#define _MAP_WND_H_

#include "window.h"


class MapWnd:public Window
{
private:
//	UnitData* pUnitData ;

public:
	enum {CELL_H_COUNT = 1, CELL_W_COUNT = 1,CELL_SIZE = 500} ;

	~MapWnd () {};

	void init (int _x, int _y) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int id) ;

//	void draw (HDC hdc) ;
} ;


#endif