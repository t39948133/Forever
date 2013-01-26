#ifndef _SHOP_WND_H_
#define _SHOP_WND_H_

#include "window.h"
#include "player.h"
#include "item_info_wnd.h"

//­I¥]µøµ¡

class ShopWnd:public Window
{
private:
	enum {CLOSE_BUTTON = 10, BUTTON_COUNT = 11, CLOSE_TEXT = 10, SHOP_TEXT = 11, TEXT_COUNT = 12, ICON_SIZE = 50} ;

	ItemInfoWnd* pItemInfoWnd ;
	WindowMan windowMan ;

#ifdef _PROJECT_OGRE_3D_	
	ImageButton* vpBtn[BUTTON_COUNT] ;
#else _PROJECT_GDI_
	TextButton* vpBtn[BUTTON_COUNT] ;
#endif
	TextArea* vpText[TEXT_COUNT];

public:

	Player* pPlayer ;
	

	~ShopWnd () {};

	void init (int _x, int _y, Player* pb) ;

	bool canDrag (int tx, int ty) ;
	void onCommand (int) ;
	void onCommandFocus (int) ;
	
#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
	void onSwitch () ;

#endif
} ;

#endif