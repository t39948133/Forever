#ifndef _CPACKETPLAYERINIT_H_
#define _CPACKETPLAYERINIT_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataBackpack.h"
#include "CNetDataSkill.h"
#include "CNetDataEquip.h"
#include "CNetDataHotKey.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketPlayerInit : public CBasePacket
{
   public:
      CPacketPlayerInit() : CBasePacket(PACKET_PLAYER_INIT)
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
      unsigned int      m_xp;             //經驗值
      unsigned int      m_xpMax;	         //最大經驗值
      long long         m_money;          //錢

      CNetDataBackpack  m_vBackpack[BACK_MAX];    //背包
      CNetDataSkill     m_vSkill[SKILL_MAX];      //技能
      CNetDataEquip     m_mEquip[MAX_SLOT];	     //裝備欄
      CNetDataHotKey    m_vHotKey[UI_HOTKEY_NUM]; //快捷鍵資料
};

#endif  // #ifndef _CPACKETPLAYERINIT_H_