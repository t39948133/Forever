#include "CButton.h"

void CButton::init(int _x, int _y, int _w, int _h, int _id)
{
   x = _x;
   y = _y;
   w = _w;
   h = _h;
	id = _id ;
}

void CButton::onLClick(int tx, int ty)
{
   pParent->onLCommand (id) ;
}

void CButton::onRClick(int tx, int ty)
{
	pParent->onRCommand (id) ;
}