#include "CFButton.h"

void CFButton::init(int _x, int _y, int _w, int _h, int _id)
{
   x = _x;
   y = _y;
   w = _w;
   h = _h;
	id = _id ;
}

void CFButton::onLClick(int tx, int ty)
{
   pParent->onLCommand (id) ;
}

void CFButton::onRClick(int tx, int ty)
{
	pParent->onRCommand (id) ;
}