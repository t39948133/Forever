#ifndef _CPACKETDEAD_H_
#define _CPACKETDEAD_H_
#include "CBasePacket.h"
#include "CUnitObject.h"

class CPacketDead : public CBasePacket
{
   public:
      CPacketDead() : CBasePacket(PACKET_DEAD)
      {
      }

      long long getUID() {
         return m_uid;
      }

      void pack(long long uid) {
         m_uid = uid;
      }

   private:
      long long m_uid;
};

#endif  // #ifndef _CPACKETDEAD_H_