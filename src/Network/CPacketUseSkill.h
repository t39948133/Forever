#ifndef _CPACKETUSESKILL_H_
#define _CPACKETUSESKILL_H_
#include "CBasePacket.h"
#include "CUnitObject.h"

class CPacketUseSkill : public CBasePacket
{
   public:
      CPacketUseSkill() : CBasePacket(PACKET_USE_SKILL)
      {
      }

      long long getUID();

      void pack(CUnitObject *pUnitObject, int skillID);
      void unpack(CUnitObject *pUnitObject);

   private:
      long long m_uid;
      long long m_targetUID;
      int m_skillID;
};

#endif  // #ifndef _CPACKETUSESKILL_H_