#ifndef _BACKPACK_WND_H_
#define _BACKPACK_WND_H_

#include "window.h"
#include "player.h"
#include "image_button.h"

//­I¥]µøµ¡
class HotKeyWnd ;
class PlayerInfoWnd ;
class BackpackWnd:public Window
{
public:
	enum {BUTTON_COUNT = 25, CELL_SIZE = 60, TEXT_COUNT = 26} ;
	
	Player* pPlayer ;
	HotKeyWnd* phkWnd ;
	PlayerInfoWnd* ppinWnd ;

#ifdef _PROJECT_OGRE_3D_	
	ImageButton* vpBtn[BUTTON_COUNT] ;
#else _PROJECT_GDI_
	TextButton* vpBtn[BUTTON_COUNT] ;
#endif
	TextArea* vpText[TEXT_COUNT];

	~BackpackWnd () {};

	void init (int _x, int _y, Player* pb, HotKeyWnd* pw, PlayerInfoWnd* ppinw) ;

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