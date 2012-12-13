#ifndef _NPC_CHAT_WND_H_
#define _NPC_CHAT_WND_H_

#include "window.h"

#include "player.h"
#include <network\\gp_socket.h>
using namespace GP ;

//背包視窗
class NPC ;
class NPCChatWnd:public Window
{
public:
	enum {QUEST_H_COUNT = 3, CHAT_H_COUNT = 3,
			CELL_SIZE = 40} ;
	Player* pPlayer ;
	NPC* pNPC ;
	NetStream* pStream ;

	enum {TYPE_CHAT, TYPE_REWARD} ;
	int type ;

	int selQuestID ;//目前選的任務編號

	TextButton* vpBtn[QUEST_H_COUNT+CHAT_H_COUNT+1] ;

	~NPCChatWnd () {};

	void init (int _x, int _y, Player* pb, NetStream* ) ;

	void setNPC (NPC*) ;
	bool canDrag (int tx, int ty) ;

	void onCommand (int) ;
//	void onClick (int tx, int ty) ;

	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif