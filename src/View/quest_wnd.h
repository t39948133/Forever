#ifndef _QUEST_WND_H_
#define _QUEST_WND_H_

#include "window.h"

#include "player.h"

//­I¥]µøµ¡
class QuestWnd:public Window
{
public:
	enum {CELL_H_COUNT = 4, CELL_SIZE = 40} ;
//	const int CELL_H_COUNT = 4 ;
//	const int CELL_SIZE = 40 ;
	Player* pPlayer ;

	~QuestWnd () {};

	void init (int _x, int _y, Player* pb) ;

	bool canDrag (int tx, int ty) ;

//	void onCommand (int) ;
//	void onClick (int tx, int ty) ;

	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif