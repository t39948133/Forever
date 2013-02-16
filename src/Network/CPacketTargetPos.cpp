#include "CPacketTargetPos.h"

#ifdef _GAMEENGINE_3D_
#include "CActionDispatch.h"
#include "CActionEvent.h"
#endif

long long CPacketTargetPos::getUID()
{
   return m_uid;
}

#ifdef _GAMEENGINE_3D_
void CPacketTargetPos::pack(CUnitObject *pUnitObject)
{
   m_uid = pUnitObject->getUID();
   m_targetPosition = pUnitObject->getTargetPosition();
}
#elif _GAMEENGINE_2D_
void CPacketTargetPos::pack(CUnitObject *pUnitObject, bool bFaceTarget)
{
   m_uid = pUnitObject->getUID();
   m_targetPosition = pUnitObject->getTargetPosition();
   m_bFaceTarget = bFaceTarget;
}
#endif

void CPacketTargetPos::unpack(CUnitObject *pUnitObject)
{
#ifdef _GAMEENGINE_3D_
   pUnitObject->setTargetPosition(m_targetPosition.fX, m_targetPosition.fY);
#elif _GAMEENGINE_2D_
   pUnitObject->setTargetPosition(m_targetPosition.fX, m_targetPosition.fY, m_bFaceTarget);
#endif

   if(pUnitObject->isReachTarget() == false) {
      CActionEvent actEvent;
      actEvent.m_event = AET_NOT_REACH;
      CActionDispatch::getInstance()->sendEvnet(pUnitObject->getMachineName(), pUnitObject->getUID(), actEvent);
   }
}

#ifdef _GAMEENGINE_3D_
void CPacketTargetPos::unpack(CPlayer3D *pPlayer)
{
   this->unpack(pPlayer->getPlayer2D());
}

void CPacketTargetPos::unpack(CMonster3D *pMonster)
{
   this->unpack(pMonster->getMonster2D());
}
#endif