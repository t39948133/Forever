#ifndef _CPACKETFIRSTLOGIN_H_
#define _CPACKETFIRSTLOGIN_H_
#include "CBasePacket.h"

class CPacketFirstLogin : public CBasePacket
{
   public:
      CPacketFirstLogin() : CBasePacket(PACKET_FIRST_LOGIN) 
      {
      }
};

#endif  // #ifndef _CPACKETFIRSTLOGIN_H_