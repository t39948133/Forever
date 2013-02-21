#include "CPacketCanUseSkill.h"

long long CPacketCanUseSkill::getUID()
{
   return m_uid;
}

long long CPacketCanUseSkill::getTargetUID()
{
   return m_targetUID;
}

int CPacketCanUseSkill::getUseSkillID()
{
   return m_skillID;
}

void CPacketCanUseSkill::setCanUseSkill(bool bCan)
{
   m_bCanUse = bCan;
}

bool CPacketCanUseSkill::canUseSkill()
{
   return m_bCanUse;
}

void CPacketCanUseSkill::pack(CUnitObject *pUnitObject, int skillID)
{
   m_uid = pUnitObject->getUID();

   if(pUnitObject->getTargetObject() != NULL)
      m_targetUID = pUnitObject->getTargetObject()->getUID();
   else
      m_targetUID = -1;

   m_skillID = skillID;
}