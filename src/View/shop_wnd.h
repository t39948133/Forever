#ifndef _SHOP_WND_H_
#define _SHOP_WND_H_

#include "window.h"

#include "player.h"

//­I¥]µøµ¡

class ShopWnd:public Window
{
private:
	static const int CELL_W_COUNT = 4 ;
	static const int CELL_H_COUNT = 4 ;
	static const int CELL_SIZE = 40 ;

public:
//	Backpack* pBackpack ;
	Player* pPlayer ;

	~ShopWnd () {};

	void init (int _x, int _y, Player* pb) ;

	bool canDrag (int tx, int ty) ;
	void onClick (int tx, int ty) ;

	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif