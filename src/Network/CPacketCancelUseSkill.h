#ifndef _CPACKETCANCELUSESKILL_H_
#define _CPACKETCANCELUSESKILL_H_
#include "CBasePacket.h"
#include "CPlayer.h"

class CPacketCancelUseSkill : public CBasePacket
{
   public:
      CPacketCancelUseSkill() : CBasePacket(PACKET_CANCEL_USESKILL)
      {
      }

      long long getUID();

      void pack(CPlayer *pPlayer);
      void unpack(CPlayer *pPlayer);

   private:
      long long m_uid;
};

#endif  // #ifndef _CPACKETCANCELUSESKILL_H_