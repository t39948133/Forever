#ifndef _SHOP_WND_H_
#define _SHOP_WND_H_

#include "window.h"

#include "player.h"

//­I¥]µøµ¡

class ShopWnd:public Window
{
private:
	enum {BUTTON_COUNT = 22, CELL_SIZE = 60, TEXT_COUNT = 13} ;

public:
//	Backpack* pBackpack ;
	Player* pPlayer ;

	~ShopWnd () {};

	void init (int _x, int _y, Player* pb) ;

	bool canDrag (int tx, int ty) ;
	void onCommand (int) ;
	
#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
	void onSwitch () ;

#endif
//	void onClick (int tx, int ty) ;
//	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif