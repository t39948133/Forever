#ifndef _PLAYER_INFO_WND_H_
#define _PLAYER_INFO_WND_H_

#include "window.h"
#include "unit.h"
#include "image_button.h"


class PlayerInfo
{
public:
	int itemID ;
} ;

class PlayerInfoWnd:public Window
{
private:
	Player* pPlayer ;
	
public:
	
	enum {BUTTON_WEAPON, BUTTON_SHIELD, BUTTON_JEWELRY_1, BUTTON_JEWELRY_2,
		BUTTON_CLOTHES, BUTTON_SPAULDER, BUTTON_PANTS, BUTTON_GLOVE, 
		BUTTON_RING_1, BUTTON_RING_2, BUTTON_SHOES, BUTTON_BELT, 
		BUTTON_ATTRIBUTE, BUTTON_PLAYER_IMAGE, BUTTON_COUNT} ;

	enum {ICON_SIZE = 50, TEXT_COUNT = 21} ;

	~PlayerInfoWnd () {};

	PlayerInfo playerInfo[BUTTON_COUNT] ;

#ifdef _PROJECT_OGRE_3D_	
	ImageButton* vpBtn[BUTTON_COUNT] ;
#else _PROJECT_GDI_
	TextButton* vpBtn[BUTTON_COUNT] ;
#endif
	TextArea* vpText[TEXT_COUNT];

	void init (int _x, int _y, Player* pPlr) ;

	bool canDrag (int tx, int ty) ;

	void onCommand (int id) ;

	void wearEquip (int _itemID) ;

#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
	void onSwitch () ;
#endif
} ;


#endif