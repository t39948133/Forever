#ifndef _PLAYER_INFO_WND_H_
#define _PLAYER_INFO_WND_H_

#include "window.h"
#include "unit.h"

class PlayerInfoWnd:public Window
{
private:
	UnitData* pUnitData ;
	TextArea* pTA ;

public:
	enum {BUTTON_COUNT = 13, CELL_SIZE = 20, TEXT_COUNT = 21} ;

	~PlayerInfoWnd () {};

	void init (int _x, int _y, UnitData* pu) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int id) ;

//	void draw (HDC hdc) ;
} ;


#endif