#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "key_state.h"
#include "easy_str.h"
#include <list>

//代表一個遊戲介面視窗
//將來可以被擴充成為背包介面,狀態介面,任務界面
class Window
{
public:
	Window* pParent ;//父親視窗
	typedef std::list <Window*> VP_WND ;
	VP_WND vpWnd ;//所有的子視窗

	int x, y ;//視窗的座標,左上角的
	int w, h ;//視窗的寬高

	bool bVisible ;

	bool checkPoint (int tx, int ty) ;

	virtual void onMove () {} ;

	virtual bool canDrag (int tx, int ty) ;
	virtual void onClick (int tx, int ty) ;

	virtual void draw (HDC hdc, int ox, int oy) ;
	virtual void setZOrder (int) {} ;

	void addChild (Window*) ;

	virtual void onCommand (int) {} ;//子視窗,按鈕button,通知

	Window ():pParent(NULL)
	{
	}
	virtual ~Window () {}
} ;

class Button:public Window
{
public:
	int id ;

public:

	void init (int _x, int _y, int _w, int _h, int _id) ;
	virtual void onClick (int tx, int ty) ;
} ;

class TextButton:public Button
{
public:
	EasyStr <64> str ;

	void draw (HDC hdc, int ox, int oy) ;
} ;

#ifdef _PROJECT_GDI_

class TextArea:public Window
{
private:
	EasyStr <256> str ;

public:
	void init (int _x, int _y, int _w, int _h) ;

	void setText (const char*, float, float, float) ;
	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif

class WindowMan//視窗管理者(manager)
{
protected:
	typedef std::list <Window*> VP_WINDOW ;
	VP_WINDOW vpWindow ;
	Window* pDragWnd ;//拖曳中的視窗

	bool bInDrag ;//代表視窗是否在拖曳中
	int dragX, dragY ;

//	KeyState keyLButton ;

	int screenX, screenY ;

	int clientX, clientY ;

public:
	WindowMan () ;

	void addWnd (Window* pw) ;

private:
	void doDrag (HWND hWnd, KeyMan&) ;

public:
	bool work (HWND hWnd, KeyMan&) ;

	void draw (HDC hdc) ;

	void deleteAllWindow () ;
} ;

#endif