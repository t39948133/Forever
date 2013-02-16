#ifndef _CPACKETMONSTERDATA_H_
#define _CPACKETMONSTERDATA_H_
#include "CBasePacket.h"
#include "CMonster.h"

#ifdef _GAMEENGINE_3D_
#include "CMonster3D.h"
#endif

class CPacketMonsterData : public CBasePacket
{
   public:
      CPacketMonsterData() : CBasePacket(PACKET_MONSTER_DATA)
      {
      }

      long long getUID();
      int getKindID();

      void pack(CMonster *pMonster);
      void unpack(CMonster *pMonster);
#ifdef _GAMEENGINE_3D_
      void unpack(CMonster3D *pMonster);
#endif

   private:
      long long             m_uid;             //唯一編號
      int                   m_kindID;          //怪物種類id
      FPOS                  m_position;        //角色X,Y座標 (2D)
      FPOS                  m_targetPosition;  //目標點X,Y座標 (2D)
      float                 m_fDirection;      //角色方向(單位: 弧度), 逆時針方向旋轉為+, 順時針方向旋轉為-, 方向為0是朝下
      MonsterState          m_state;           //目前狀態
      FPOS                  m_bornPosition;    //出生X,Y座標 (2D)
      FPOS                  m_anchorPosition;  //進入戰鬥定位點
};

#endif  // #ifndef _CPACKETMONSTERDATA_H_