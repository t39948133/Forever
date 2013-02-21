#ifndef _CPACKETCANUSESKILL_H_
#define _CPACKETCANUSESKILL_H_
#include "CBasePacket.h"
#include "CUnitObject.h"

class CPacketCanUseSkill : public CBasePacket
{
   public:
      CPacketCanUseSkill() : CBasePacket(PACKET_CAN_USE_SKILL)
      {
      }

      long long getUID();
      long long getTargetUID();
      int getUseSkillID();
      void setCanUseSkill(bool bCan);
      bool canUseSkill();

      void pack(CUnitObject *pUnitObject, int skillID);

   private:
      long long m_uid;
      long long m_targetUID;
      int       m_skillID;
      bool      m_bCanUse;
};

#endif  // #ifndef _CPACKETCANUSESKILL_H_