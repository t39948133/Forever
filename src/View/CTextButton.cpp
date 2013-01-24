#include "CTextButton.h"

void CTextButton::draw(HDC hdc, int ox, int oy)
{
	CButton::draw(hdc, ox, oy) ;
   TextOut(hdc, x+ox+2, y+oy+2, str.c_str(), str.size()) ;
}