#ifndef _GP_KEY_STATE_
#define _GP_KEY_STATE_

#include <graphic\gp_geometry.h>
#include <math.h>

namespace GP
{


//#########################################
//#########################################
//#########################################

//按鍵狀態
class KeyState
{
private:
	enum {NO_ID = -1} ;
	int id ;
	bool bPreDown ;//上次
	bool bCurDown ;


public:

	KeyState () ;
	void work () ;


	void setID (int) ;

	bool isDown ()const ;
	bool isTriggerDown ()const ;
	bool isTriggerUp ()const ;
} ;

enum {KEY_LBUTTON, KEY_RBUTTON,
	KEY_SPACE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_COUNT} ;

class KeyStateMan
{
public:

private:
	//所有的按鍵
	KeyState vKeyState[KEY_COUNT] ;

	Point2F cursorPos ;//游標位置
public:

	KeyStateMan () ;
	void work (HWND, int, float32, float32) ;

	const Point2F& getCursorCanvasPos ()const ;

	bool isDown (unsigned int)const ;//狀態
	bool isTriggerDown (unsigned int)const ;//是否為按下瞬間
	bool isTriggerUp (unsigned int)const ;//是否為放開瞬間
} ;

}

#endif