#ifndef _ITEMINFO_WND_H_
#define _ITEMINFO_WND_H_

#include "window.h"
#include "image_button.h"

class ItemInfoWnd:public Window
{
private:
	enum {TEXT_COUNT = 1} ;
	TextArea* vpText[TEXT_COUNT] ;

public:

	~ItemInfoWnd () {};

	void init (int _x, int _y) ;

	void setItem (const char*) ;
	void setPos (int _x, int _y) ;
	void show (bool bs) ;
	void draw (HDC hdc, int ox, int oy) ;

} ;

#endif