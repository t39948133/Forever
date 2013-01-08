#ifndef _PLAYER_STATUS_WND_H_
#define _PLAYER_STATUS_WND_H_

#include "window.h"
#include "player.h"

class PlayerStatusWnd:public Window
{
private:
	Player* pPlayer ;
	enum {BUTTON_HP, BUTTON_MP, BUTTON_XP, BUTTON_COUNT = 3, CELL_SIZE = 20, TEXT_COUNT = 3} ;
	
	TextButton* pvBtn[BUTTON_COUNT] ;
public:
	~PlayerStatusWnd () {};

	void init (int _x, int _y, Player* pu) ;
	
	bool canDrag (int tx, int ty) ;

	void onCommand (int) ;

	void upDate () ;


#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
#endif

//	void draw (HDC hdc) ;
} ;


#endif