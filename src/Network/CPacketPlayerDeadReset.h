#ifndef _CPACKETPLAYERDEADRESET_H_
#define _CPACKETPLAYERDEADRESET_H_
#include "CBasePacket.h"
#include "CPlayer.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketPlayerDeadReset : public CBasePacket
{
   public:
      CPacketPlayerDeadReset() : CBasePacket(PACKET_PLAYER_DEAD_RESET)
      {
      }

      long long getUID();
      long long getTargetUID();
      void pack(CPlayer *pPlayer);
      void unpack(CPlayer *pPlayer);
#ifdef _GAMEENGINE_3D_
      void unpack(CPlayer3D *pPlayer3D);
#endif

   private:
      long long         m_uid;            //唯一編號
      FPOS              m_position;       //角色X,Y座標 (2D)
      FPOS              m_targetPosition; //目標點X,Y座標 (2D)
      float             m_fDirection;     //角色方向(單位: 弧度), 逆時針方向旋轉為+, 順時針方向旋轉為-, 方向為0是朝下
      long long         m_targetUID;      //目標物
};

#endif  // #ifndef _CPACKETPLAYERDEADRESET_H_