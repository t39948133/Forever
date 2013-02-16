#include "CPacketTargetObject.h"

long long CPacketTargetObject::getUID()
{
   return m_uid;
}

long long CPacketTargetObject::getTargetUID()
{
   return m_targetUID;
}

void CPacketTargetObject::pack(CUnitObject *pUnitObject)
{
   m_uid = pUnitObject->getUID();

   if(pUnitObject->getTargetObject() != NULL)
      m_targetUID = pUnitObject->getTargetObject()->getUID();
   else
      m_targetUID = -1;
}