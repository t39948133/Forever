#include "CPacketAdvAttrData.h"

long long CPacketAdvAttrData::getUID()
{
   return m_uid;
}

void CPacketAdvAttrData::pack(CUnitObject *pUnitObject)
{
   m_uid            = pUnitObject->getUID();
   m_advAttr        = pUnitObject->getAdvAttr();
}

void CPacketAdvAttrData::unpack(CUnitObject *pUnitObject)
{
   if(pUnitObject->getUID() != m_uid)
      return;

   pUnitObject->setAdvAttr(m_advAttr);
}