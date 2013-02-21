#ifndef _CPACKETBACKPACKDATA_H_
#define _CPACKETBACKPACKDATA_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataBackpack.h"

class CPacketBackpackData : public CBasePacket
{
   public:
      CPacketBackpackData() : CBasePacket(PACKET_BACKPACK_DATA)
      {
      }

      long long getUID();
      void pack(CPlayer *pPlayer);
      void unpack(CPlayer *pPlayer);

   private:
      long long         m_uid;            //°ß¤@½s¸¹

      CNetDataBackpack  m_vBackpack[BACK_MAX];    //­I¥]
};

#endif  // #ifndef _CPACKETBACKPACKDATA_H_