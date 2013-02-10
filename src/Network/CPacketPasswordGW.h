#ifndef _CPACKETPASSWORDGW_H_
#define _CPACKETPASSWORDGW_H_
#include "CBasePacket.h"

class CPacketPasswordGW : public CBasePacket
{
   public:
      long long m_netID;

      CPacketPasswordGW() : CBasePacket(PACKET_PASSWORD_GW) 
      {
      }
};

#endif  // #ifndef _CPACKETPASSWORDGW_H_