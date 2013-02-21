#ifndef _CPACKETEQUIPDATA_H_
#define _CPACKETEQUIPDATA_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataEquip.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketEquipData : public CBasePacket
{
   public:
      CPacketEquipData() : CBasePacket(PACKET_EQUIP_DATA)
      {
      }

      long long getUID();
      void pack(CPlayer *pPlayer, EquipSlot equipSlot, int itemId);
      void unpack(CPlayer *pPlayer);
#ifdef _GAMEENGINE_3D_
      void unpack(CPlayer3D *pPlayer3D);
#endif

   private:
      long long      m_uid;        //唯一編號
      CNetDataEquip  m_mEquip;	  //裝備欄
};

#endif  // #ifndef _CPACKETEQUIPDATA_H_