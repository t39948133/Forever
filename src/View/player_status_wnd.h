#ifndef _PLAYER_STATUS_WND_H_
#define _PLAYER_STATUS_WND_H_

#include "window.h"
#include "unit.h"

class PlayerStatusWnd:public Window
{
private:
	UnitData* pUnitData ;

public:
	~PlayerStatusWnd () {};

	void init (int _x, int _y, UnitData* pu) ;

	void draw (HDC hdc) ;
} ;


#endif