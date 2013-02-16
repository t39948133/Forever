#ifndef _CBASEPACKET_H_
#define _CBASEPACKET_H_
#include "Common.h"

enum {
   PACKET_FIRST_LOGIN, PACKET_PASSWORD_GW, PACKET_PLAYER_DATA_WG, PACKET_PLAYER_INIT, // 登入流程封包
   PACKET_PLAYER_DATA,   // 玩家資料封包
   PACKET_TARGET_POS,    // 目標位置封包
   PACKET_MONSTER_DATA,  // 怪物資料封包
   PACKET_TARGET_OBJECT, // 目標物封包
   PACKET_ACTION_EVENT,  // 動作系統訊息
   PACKET_USE_SKILL,     // 使用技能
};

class CBasePacket
{
   public:
      int m_id;

      CBasePacket(int id) {
         m_id = id;
      }
};

#endif  // #ifndef _CBASEPACKET_H_