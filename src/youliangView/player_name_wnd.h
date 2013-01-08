#ifndef _PLAYER_NAME_WND_H_
#define _PLAYER_NAME_WND_H_

#include "window.h"
#include "unit.h"

class PlayerNameWnd:public Window
{
private:
	UnitData* pUnitData ;

public:
	enum {CELL_H_COUNT = 1, CELL_W_COUNT = 4,CELL_SIZE = 20} ;

	~PlayerNameWnd () {};

	void init (int _x, int _y, UnitData* pu) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int id) ;

//	void draw (HDC hdc) ;
} ;


#endif