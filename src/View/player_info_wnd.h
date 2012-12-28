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
	
	enum {BUTTON_SPAULDER, BUTTON_GLOVE, BUTTON_WEAPON, BUTTON_CLOTHES,
	BUTTON_PANTS, BUTTON_SHIELD, BUTTON_SHOES, BUTTON_UI_NAME, BUTTON_PLAYER_NAME, 
	BUTTON_LEVEL_EXP, BUTTON_ATTRIBUTE, BUTTON_PLAYER_IMAGE, BUTTON_COUNT} ;

	enum {CELL_SIZE = 20, TEXT_COUNT = 21} ;

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

//	void draw (HDC hdc) ;
} ;


#endif