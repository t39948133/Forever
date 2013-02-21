#include "CPacketCancelUseSkill.h"

long long CPacketCancelUseSkill::getUID()
{
   return m_uid;
}

void CPacketCancelUseSkill::pack(CPlayer *pPlayer)
{
   m_uid = pPlayer->getUID();
}

void CPacketCancelUseSkill::unpack(CPlayer *pPlayer)
{
   if(pPlayer->getUID() != m_uid)
      return;

   pPlayer->cancelCastSkill();
}