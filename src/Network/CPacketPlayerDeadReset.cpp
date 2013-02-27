#include "CPacketPlayerDeadReset.h"

long long CPacketPlayerDeadReset::getUID()
{
   return m_uid;
}

long long CPacketPlayerDeadReset::getTargetUID()
{
   return m_targetUID;
}

void CPacketPlayerDeadReset::pack(CPlayer *pPlayer)
{
   m_uid            = pPlayer->getUID();
   m_position       = pPlayer->getPosition();
   m_targetPosition = pPlayer->getTargetPosition();
   m_fDirection     = pPlayer->getDirection();

   CUnitObject *pUnitObject = pPlayer->getTargetObject();
   if(pUnitObject != NULL)
      m_targetUID = pUnitObject->getUID();
   else
      m_targetUID = -1;
}

void CPacketPlayerDeadReset::unpack(CPlayer *pPlayer)
{
   if(pPlayer->getUID() != m_uid)
      return;

   pPlayer->setPosition(m_position.fX, m_position.fY);
   pPlayer->setTargetPosition(m_targetPosition.fX, m_targetPosition.fY);
   pPlayer->setDirection(m_fDirection);
}

#ifdef _GAMEENGINE_3D_
void CPacketPlayerDeadReset::unpack(CPlayer3D *pPlayer3D)
{
   this->unpack(pPlayer3D->getPlayer2D());

   // ªZ¾¹¦¬¦^
   pPlayer3D->notifyPutinWeapon();
}
#endif