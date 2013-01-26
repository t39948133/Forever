#ifndef _GAME_CLIENT_H_
#define _GAME_CLIENT_H_

#include <list>

#include "scene.h"
#include "fps_time.h"
#include "map_wnd.h"
#include "backpack_wnd.h"
#include "skill_wnd.h"
#include "target_info_wnd.h"
#include "npc_chat_wnd.h"
#include "quest_wnd.h"
#include "player_image_wnd.h"
#include "hotkey_wnd.h"
#include "player_status_wnd.h"
#include "player_info_wnd.h"
#include "mini_map_wnd.h"
#include "player_name_wnd.h"
#include "tool_bar_wnd.h"
#include "shop_wnd.h"
#include "hotkey_wnd.h"
#include "skill_info_wnd.h"
#include "item_info_wnd.h"

#include "net_packet.h"

#include <network\\gp_socket.h>

#ifdef _PROJECT_OGRE_3D_
	#include "window_ogre.h"
#else
#endif


using namespace GP ;

class GameClient
{
private:
	FPS fps ;

protected:
	Scene scene ;//

public:
	enum {STATE_LOGIN, //第一次進入遊戲的登入(打完帳號密碼後進入遊戲)
			STATE_CHANGE_LOGIN,//切地圖的登入
			STATE_PLAY} ;
	int gameState ;
	bool bSendLogin ;//有送出login資訊

	float targetX, targetY ;

	NetStream stream ;

	KeyMan keyMan ;
	TeamInfo teamInfo ;

	ItemInfoWnd* pItemInfoWnd ;
	SkillInfoWnd* pSkillInfoWnd ;
	MapWnd* pmw ;
	PlayerInfoWnd* ppinw ;
	HotKeyWnd* phw ;
	BackpackWnd* pbw ;
	TargetInfoWnd* pTargetInfoWnd ; 
	SkillWnd* pSkillWnd ;
	ShopWnd* psw ;
	NPCChatWnd* pNPCWnd ;
	QuestWnd* pqw ;
	PlayerImageWnd* ppimw ;
	PlayerStatusWnd* ppsw ;
	PlayerNameWnd* ppnw ;
	MiniMapWnd* pmmw ;
	ToolBarWnd* ptw ;
	

#ifdef _PROJECT_OGRE_3D_
	WindowManOgre windowMan ;
#else
	WindowMan windowMan ;
#endif

public:
	float cameraDir ;

	void initUI () ;

	void init (const char* name, float x, float y) ;

	void onRecvPlayerInit (PacketPlayerInit& pkg) ;

	virtual Player* onRecvPlayerData (PacketPlayerData& pkg) ;

	virtual Monster* onRecvMonsterData (PacketMonsterData& pkg) ;
	virtual NPC* onRecvNPCData (PacketNPCData& pkg) ;

	void onRecvHP (PacketHP& pkg) ;
	void onRecvAddQuest (PacketAddQuest& pkg) ;
	void onRecvDelQuest (PacketDelQuest& pkg) ;
	void onRecvFinishQuest (PacketFinishQuest& pkg) ;

	void onRecvTargetPos (PacketTargetPos& pkg) ;

	void onRecvDoAction (PacketDoAction& pkg) ;

	void onRecvSetBackpack (PacketSetBackpack& pkg) ;

	void onRecvUseSkill (PacketUseSkill& pkg) ;
	virtual void onRecvChangeGameServer (PacketChangeGameServer& pkg) ;
	virtual void onRecvDelMonster (PacketDelMonster& pkg) ;
	virtual void onRecvFormTeamGC (PacketFormTeamGC& pkg) ;
	virtual void onRecvTeamInfo (PacketTeamInfo& pkg) ;
	

	void onClikcNPC (NPC&) ;
	void onClickPlayer (Player&) ;

	void doUI (HWND hWnd) ;

	void work_login (HWND hWnd, bool bActive) ;
	void work_change_login (HWND hWnd, bool bActive) ;
	void work_play (HWND hWnd, bool bActive) ;

	void work (HWND hWnd, bool bActive) ;

	void draw (HDC hdc) ;
} ;


#endif