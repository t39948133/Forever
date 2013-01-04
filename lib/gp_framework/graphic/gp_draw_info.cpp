#include "gp_draw_info.h"

#include <assert.h>

namespace GP
{

DrawInfo::DrawInfo ():blendType(NO_BLEND),alpha(1),bFillColor(false)
{
}

void DrawInfo::setFillColor (bool b, const Color& color)//¶ñ¦â
{
	bFillColor = b ;
	fillColor = color ;
}

void DrawInfo::setBlend (int type, float32 a)
{
	blendType = type ;
	alpha = a; 
}



}