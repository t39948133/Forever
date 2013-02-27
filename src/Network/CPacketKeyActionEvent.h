#ifndef _CPACKETKEYACTIONEVENT_H_
#define _CPACKETKEYACTIONEVENT_H_
#include "CBasePacket.h"
#include "CUnitObject.h"
#include "CKeyActionEvent.h"

class CPacketKeyActionEvent : public CBasePacket
{
   public:
      CPacketKeyActionEvent() : CBasePacket(PACKET_KEY_ACTION_EVENT)
      {
      }

      long long getUID();
      int getKey();

      void pack(CUnitObject *pUnitObject, CKeyActionEvent *pActionEvent);
      void unpack(CUnitObject *pUnitObject);

   private:
      long long m_uid;
      ACTION_EVENT_TYPE m_event;
      int m_iKeyID;  // «öÁä(¨Ï¥ÎVirtual key)
};

#endif  // #ifndef _CPACKETKEYACTIONEVENT_H_