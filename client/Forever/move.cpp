#include "move.h"

void PlayerMove(Cplayer& player)
{
	float x=0,y=0;
	if(GetAsyncKeyState(VK_UP)<0)
	{
		y--;
	}
	if(GetAsyncKeyState(VK_DOWN)<0)
	{
		y++;
	}
	if(GetAsyncKeyState(VK_LEFT)<0)
	{
		x--;
	}
	if(GetAsyncKeyState(VK_RIGHT)<0)
	{
		x++;
	}
	player.move(x,y);
}

void PlayerMove_WASD(Cplayer& player)
{
	float x=0,y=0;
	if(GetAsyncKeyState(0x57)<0)
	{
		y--;
	}
	if(GetAsyncKeyState(0x53)<0)
	{
		y++;
	}
	if(GetAsyncKeyState(0x41))
	{
		x--;
	}
	if(GetAsyncKeyState(0x44))
	{
		x++;
	}
	player.move(x,y);
}



void PlayerJump(Cplayer& player)
{
	if(GetAsyncKeyState(VK_SPACE)<0)
	{
		player.jump();
	}
}