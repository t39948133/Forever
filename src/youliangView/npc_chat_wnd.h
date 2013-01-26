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
	enum {TEXT_COUNT = 8, CELL_SIZE = 20} ;
	Player* pPlayer ;
	NPC* pNPC ;
	NetStream* pStream ;

	enum {TYPE_CHAT, TYPE_REWARD} ;
	int type ;

	int selQuestID ;//目前選的任務編號

	TextButton* vpBtn[TEXT_COUNT] ;

	~NPCChatWnd () {};

	void init (int _x, int _y, Player* pb, NetStream* ) ;

	void setNPC (NPC*) ;
	bool canDrag (int tx, int ty) ;

	void onCommand (int) ;

#ifdef _PROJECT_OGRE_3D_
	void onMove () ;
	void setZOrder (int z) ;
#endif
} ;

#endif