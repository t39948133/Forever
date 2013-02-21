#ifndef _CPACKETADVATTRDATA_H_
#define _CPACKETADVATTRDATA_H_
#include "CBasePacket.h"
#include "CUnitObject.h"

class CPacketAdvAttrData : public CBasePacket
{
   public:
      CPacketAdvAttrData() : CBasePacket(PACKET_ADVATTR_DATA)
      {
      }

      long long getUID();
      void pack(CUnitObject *pUnitObject);
      void unpack(CUnitObject *pUnitObject);

   private:
      long long         m_uid;            //°ß¤@½s¸¹
      AdvancedAttribute m_advAttr;        //ÄÝ©Ê
};

#endif  // #ifndef _CPACKETADVATTRDATA_H_