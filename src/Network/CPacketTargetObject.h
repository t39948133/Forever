#ifndef _CPACKETTARGETOBJECT_H_
#define _CPACKETTARGETOBJECT_H_
#include "CBasePacket.h"
#include "CUnitObject.h"

class CPacketTargetObject : public CBasePacket
{
   public:
      CPacketTargetObject() : CBasePacket(PACKET_TARGET_OBJECT)
      {
      }

      long long getUID();
      long long getTargetUID();

      void pack(CUnitObject *pUnitObject);

   private:
      long long m_uid;
      long long m_targetUID;
};

#endif  // #ifndef _CPACKETTARGETOBJECT_H_