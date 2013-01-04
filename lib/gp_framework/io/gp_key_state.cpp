#include "gp_key_state.h"
#include <graphic\gp_canvas.h>

#include <assert.h>

#include <system\gp_variable_type.h>

namespace GP
{

KeyState::KeyState ():bPreDown(false),bCurDown(false),id(NO_ID)
{

}

void KeyState::work ()
{
	assert ((id != NO_ID) && "KeyState::work") ;

	bPreDown = bCurDown ;
	bCurDown = GetAsyncKeyState (id) < 0 ;
}

void KeyState::setID (int i)
{
	id = i ;
}

bool KeyState::isDown ()const
{
	return bCurDown ;
}

bool KeyState::isTriggerDown ()const
{
	return bCurDown && !(bPreDown) ;
}

bool KeyState::isTriggerUp ()const
{
	return !bCurDown && bPreDown ;
}

KeyStateMan::KeyStateMan ()
{
	vKeyState[KEY_LBUTTON].setID (VK_LBUTTON) ;
	vKeyState[KEY_RBUTTON].setID (VK_RBUTTON) ;

	vKeyState[KEY_SPACE].setID (VK_SPACE) ;
	vKeyState[KEY_UP].setID (VK_UP) ;

	vKeyState[KEY_DOWN].setID (VK_DOWN) ;
	vKeyState[KEY_LEFT].setID (VK_LEFT) ;
	vKeyState[KEY_RIGHT].setID (VK_RIGHT) ;
}

void KeyStateMan::work (HWND hWnd, int coordiateSystem,
						float32 canvasW, float32 canvasH)
{
	if (GetActiveWindow () != hWnd)
		return ;//不是工作中


	POINT pnt ;
	GetCursorPos (&pnt) ;
	ScreenToClient (hWnd, &pnt) ;

//	if (b2DPixelMode)
	if (coordiateSystem == Canvas::COORDINATE_SCREEN)
	{
		//2D pixel mode
		cursorPos.x = (float)pnt.x-canvasW/2 ;
//		cursorPos.y = -(canvasH/2-(float)pnt.y) ;
		cursorPos.y = (canvasH/2-(float)pnt.y) ;
	}else if (coordiateSystem == Canvas::COORDINATE_2D)
	{
		cursorPos.x = (float)pnt.x-canvasW/2 ;
		cursorPos.y = canvasH/2-(float)pnt.y ;
	}else
	{
		cursorPos.x = (float)pnt.x ;
		cursorPos.y = (float)pnt.y ;
	}

	for (int i = 0; i<KEY_COUNT; i++)
		vKeyState[i].work () ;
}

const Point2F& KeyStateMan::getCursorCanvasPos ()const
{
	return cursorPos ;
}

bool KeyStateMan::isDown (unsigned int offset)const//狀態
{
	assert ((offset < KEY_COUNT) && "KeyStateMan::isDown") ;

	if (offset < KEY_COUNT)
		return vKeyState[offset].isDown () ;
	return false ;
}

bool KeyStateMan::isTriggerDown (unsigned int offset)const//是否為按下瞬間
{
	assert ((offset < KEY_COUNT) && "KeyStateMan::isTriggerDown") ;

	if (offset < KEY_COUNT)
		return vKeyState[offset].isTriggerDown () ;
	return false ;
}

bool KeyStateMan::isTriggerUp (unsigned int offset)const
{
	assert ((offset < KEY_COUNT) && "KeyStateMan::isTriggerUp") ;

	if (offset < KEY_COUNT)
		return vKeyState[offset].isTriggerUp () ;
	return false ;
}

} 
