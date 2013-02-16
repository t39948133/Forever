#ifndef _CPACKETACTIONEVENT_H_
#define _CPACKETACTIONEVENT_H_
#include "CBasePacket.h"
#include "CUnitObject.h"
#include "CActionEvent.h"

class CPacketActionEvent : public CBasePacket
{
   public:
      CPacketActionEvent() : CBasePacket(PACKET_ACTION_EVENT)
      {
      }

      long long getUID();

      void pack(CUnitObject *pUnitObject, CActionEvent *pActionEvent);
      void unpack(CUnitObject *pUnitObject);

   private:
      long long m_uid;
      ACTION_EVENT_TYPE m_event;
};

#endif  // #ifndef _CPACKETACTIONEVENT_H_