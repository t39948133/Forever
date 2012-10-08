#include "unit.h"

void Cunit::draw(HDC hdc)
{
};

void Cplayer::move(float _x,float _y,float _z)
{
	if(_x>0&&_y>0)
	{
		float L=tangleL(x,y,x+_x,y+_y);
		x+=_x/L*MOVE;
		y+=_y/L*MOVE;
	}
	else
	{
		x+=_x*MOVE;
		y+=_y*MOVE;
	}
}

void Cplayer::jump()
{
};