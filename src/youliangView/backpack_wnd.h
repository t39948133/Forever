#ifndef _BACKPACK_WND_H_
#define _BACKPACK_WND_H_

#include "window.h"
#include "player.h"
#include "image_button.h"
#include "item_info_wnd.h"

//­I¥]µøµ¡
class HotKeyWnd ;
class PlayerInfoWnd ;
class BackpackWnd:public Window
{
public:
	enum {BUTTON_COUNT = 25, ICON_SIZE = 50, TEXT_COUNT = 26} ;
	
	ItemInfoWnd* pItemInfoWnd ;

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

	void upDate (Player* pb) ;

	void init (int _x, int _y, Player* pb, HotKeyWnd* pw, PlayerInfoWnd* ppinw, ItemInfoWnd* pItemInfoWnd) ;

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