#ifndef _HOTKEY_WND_H_
#define _HOTKEY_WND_H_

#include "window.h"
#include "unit.h"
#include "player.h"
#ifdef _PROJECT_OGRE_3D_
	#include "image_button.h"
#endif

class HotKeyInfo
{
public:
	enum {TYPE_NULL, TYPE_FOOD, TYPE_SKILL} ;
	int type ;

	int itemID ;
	int skillID ;
} ;

class HotKeyWnd:public Window
{
private:
//	UnitData* pUnitData ;

public:
	enum {BUTTON_COUNT = 10, CELL_SIZE = 40, TEXT_COUNT = 20} ;

	HotKeyInfo hotKeyInfo[BUTTON_COUNT] ;

#ifdef _PROJECT_OGRE_3D_	
	ImageButton* vpBtn[BUTTON_COUNT] ;
#else _PROJECT_GDI_
	TextButton* vpBtn[BUTTON_COUNT] ;
#endif
	TextArea* vpText[TEXT_COUNT];

	Player* pPlayer ;

	~HotKeyWnd () {};

	void init (int _x, int _y, Player* pPlr) ;

	bool canDrag (int tx, int ty) ;
	void addFoodHotKey (int id, int _itemID) ;
	void addSkillHotKey (int id) ;

	void onCommand (int id) ;
	void onCommandR (int id) ;

#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
#endif

//	void draw (HDC hdc) ;
} ;


#endif