#include "CTextArea.h"

void CTextArea::init (int _x, int _y, int _w, int _h)
{
   m_iAlignment = DT_LEFT;
   x = _x;
   y = _y;
   w = _w;
   h = _h;
}

void CTextArea::setText (std::string s, float, float, float)
{
	str = s ;
}

void CTextArea::setAlignment(int alignment)
{
   m_iAlignment = alignment;
}

void CTextArea::draw (HDC hdc, int ox, int oy)
{
   RECT rect;
   rect.left = x + ox + 2;
   rect.top = y + oy + 2;
   rect.right = rect.left + w;
   rect.bottom = rect.top + h;

   DrawText(hdc, str.c_str(), (int)str.size(), &rect, m_iAlignment | DT_WORDBREAK);
   //TextOut (hdc, x+ox+2, y+oy+2, str.c_str(), str.size()) ;
}