/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPacketXP.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/17 */
#ifndef _CPACKETXP_H_
#define _CPACKETXP_H_
#include "CBasePacket.h"

class CPacketXP : public CBasePacket
{
   public:
      CPacketXP() : CBasePacket(PACKET_XP)
      {
      }

      long long    m_uid;
	   unsigned int m_offsetXP;
};

#endif  // #ifndef _CPACKETXP_H_