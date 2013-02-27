/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPacketMoney.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/17 */
#ifndef _CPACKETMONEY_H_
#define _CPACKETMONEY_H_
#include "CBasePacket.h"

class CPacketMoney : public CBasePacket
{
   public:
      CPacketMoney() : CBasePacket(PACKET_MONEY)
      {
      }

      long long m_uid;
	   long long m_offsetMoney;
};

#endif  // #ifndef _CPACKETMONEY_H_