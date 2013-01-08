#ifndef _QUEST_WND_H_
#define _QUEST_WND_H_

#include "window.h"
#include "player.h"

//­I¥]µøµ¡
class QuestWnd:public Window
{
public:
	enum {TEXT_COUNT = 8, CELL_SIZE = 20} ;

	Player* pPlayer ;

	~QuestWnd () {};

	void init (int _x, int _y, Player* pb) ;

	bool canDrag (int tx, int ty) ;
	void onCommand (int id) ;

#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
	void onSwitch () ;
#endif

//	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif