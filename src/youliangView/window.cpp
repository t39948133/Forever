#include "window.h"

bool Window::checkPoint (int tx, int ty)
{
	if (bVisible == false)
		return false ;

	if ((tx >= x) && (tx < (x+w)) &&
		(ty >= y) && (ty < (y+h)))
		return true ;
	else
		return false ;
}

bool Window::canDrag (int tx, int ty)
{
	return true ;
}

void Window::onClick (int tx, int ty)
{
	tx -= x ;
	ty -= y ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			if ((*pi)->checkPoint (tx, ty))
			{
				(*pi)->onClick (tx, ty) ;
				break ;
			}

		++ pi ;
	}

	if (pi == vpWnd.end ())
	{
		//沒按到子視窗
	}
}

void Window::draw (HDC hdc, int ox, int oy)
{
	Rectangle (hdc, x+ox, y+oy, x+ox+w, y+oy+h) ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			(*pi)->draw (hdc, x+ox, y+oy) ;
		++ pi ;
	}
}

void Window::addChild (Window* pw)
{
	pw->pParent = this ;
	vpWnd.push_back (pw) ;
}

WindowMan::WindowMan ()
{
	pDragWnd = NULL ;
	bInDrag = false ;

//		keyLButton.setKey (VK_LBUTTON) ;
}

void WindowMan::addWnd (Window* pw)
{
	pw->pParent = NULL ;
	vpWindow.push_back (pw) ;
}

//########################

void Button::init (int _x, int _y, int _w, int _h, int _id)
{
	x = _x ;
	y = _y ;
	w = _w ;
	h = _h ;
	id = _id ;
}

void Button::onClick (int tx, int ty)
{
	pParent->onCommand (id) ;
}

//########################

void TextButton::draw (HDC hdc, int ox, int oy)
{
	Button::draw (hdc, ox, oy) ;
	TextOut (hdc, x+ox+2, y+oy+2, str, str.length ()) ;
}

#ifdef _PROJECT_GDI_

	void TextArea::init (int _x, int _y, int _w, int _h)
	{
		x = _x ;
		y = _y ;
		w = _w ;
		h = _h ;
	}

void TextArea::setText (const char* ps, float, float, float)
{
	str = ps ;
}

void TextArea::draw (HDC hdc, int ox, int oy)
{
	TextOut (hdc, x+ox+2, y+oy+2, str, str.length ()) ;
}

#endif


void WindowMan::doDrag (HWND hWnd, KeyMan& keyMan)
{
	//拖曳視窗中
//	if (keyLButton.isDown ())
	if (keyMan.isDown (KEY_LBUTTON))
	{
		//繼續壓著
		int dx = clientX - dragX ;//滑鼠拖曳多遠
		int dy = clientY - dragY ;//滑鼠拖曳多遠

		pDragWnd->x += dx ;
		pDragWnd->y += dy ;

		pDragWnd->onMove () ;

		dragX = clientX ;
		dragY = clientY ;
	}else
	{
		//放開
		bInDrag = false ;
	}
}

bool WindowMan::work (HWND hWnd, 
							KeyMan& keyMan)
{
	bool bPressWindow = false ;

	getMouseScreenPos (screenX, screenY) ;
	getMousePos (hWnd, clientX, clientY) ;

	if (bInDrag)
	{
		doDrag (hWnd, keyMan) ;
	}else
	{
		//不是拖曳視窗
		if (keyMan.isPress (KEY_LBUTTON))
		{
			//壓下去的瞬間
			VP_WINDOW::iterator pi = vpWindow.begin () ;
			while (pi != vpWindow.end ())
			{
				if ((*pi)->checkPoint (clientX, clientY))
				{
					int tx = clientX ;
					int ty = clientY ;

					if ((*pi)->canDrag (tx-(*pi)->x, 
										ty-(*pi)->y))
					{
						//可以拖曳
						bInDrag = true ;
					}else
					{
						//不可以拖曳
						(*pi)->onClick (tx, ty) ;
					}

					//有按到
					bPressWindow = true ;

					dragX = clientX ;
					dragY = clientY ;

					vpWindow.push_front (*pi) ;

					vpWindow.erase (pi) ;
					pDragWnd = vpWindow.front () ;

					break ;
				}

				++ pi ;
			}
		}else
		{
		}
	}

	return bPressWindow ;
}


	void WindowMan::draw (HDC hdc)
	{
		VP_WINDOW::reverse_iterator pi = vpWindow.rbegin () ;
		while (pi != vpWindow.rend ())
		{
			if ((*pi)->bVisible)
				(*pi)->draw (hdc, 0, 0) ;
			++ pi ;
		}
	}

	void WindowMan::deleteAllWindow ()
	{
		VP_WINDOW::reverse_iterator pi = 
				vpWindow.rbegin () ;
		while (pi != vpWindow.rend ())
		{
			delete *pi ;

			++pi ;
		}
	}
