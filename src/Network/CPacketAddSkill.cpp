#include "CPacketAddSkill.h"

long long CPacketAddSkill::getUID()
{
   return m_uid;
}

void CPacketAddSkill::pack(CPlayer *pPlayer, int skillID)
{
   m_uid              = pPlayer->getUID();
   m_vSkill.m_skillID = skillID;
}

void CPacketAddSkill::unpack(CPlayer *pPlayer)
{
   if(pPlayer->getUID() != m_uid)
      return;

   if(m_vSkill.m_skillID != -1)
      pPlayer->addSkill(m_vSkill.m_skillID);
}