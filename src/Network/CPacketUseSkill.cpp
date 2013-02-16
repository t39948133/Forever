#include "CPacketUseSkill.h"

long long CPacketUseSkill::getUID()
{
   return m_uid;
}

void CPacketUseSkill::pack(CUnitObject *pUnitObject, int skillID)
{
   m_uid = pUnitObject->getUID();

   if(pUnitObject->getTargetObject() != NULL)
      m_targetUID = pUnitObject->getTargetObject()->getUID();
   else
      m_targetUID = -1;

   m_skillID = skillID;
}

void CPacketUseSkill::unpack(CUnitObject *pUnitObject)
{
   // Todo: 暫時不處理targetUID

   pUnitObject->startCastSkill(m_skillID);
}