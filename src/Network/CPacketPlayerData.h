#ifndef _CPACKETPLAYERDATA_H_
#define _CPACKETPLAYERDATA_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataSkill.h"
#include "CNetDataEquip.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketPlayerData : public CBasePacket
{
   public:
      CPacketPlayerData() : CBasePacket(PACKET_PLAYER_DATA)
      {
      }

      long long getUID();
      void pack(CPlayer *pPlayer);
      void unpack(CPlayer *pPlayer);
#ifdef _GAMEENGINE_3D_
      void unpack(CPlayer3D *pPlayer3D);
#endif

   private:
      long long         m_uid;            //唯一編號
      char              m_level;          //等級
      std::string       m_strName;        //名字
      BasicAttribute    m_basAttr;        //基本數值
      AdvancedAttribute m_advAttr;        //屬性
      FPOS              m_position;       //角色X,Y座標 (2D)
      FPOS              m_targetPosition; //目標點X,Y座標 (2D)
      float             m_fDirection;     //角色方向(單位: 弧度), 逆時針方向旋轉為+, 順時針方向旋轉為-, 方向為0是朝下

      CNetDataSkill     m_vSkill[SKILL_MAX];      //技能
      CNetDataEquip     m_mEquip[MAX_SLOT];	     //裝備欄
};

#endif  // #ifndef _CPACKETPLAYERDATA_H_