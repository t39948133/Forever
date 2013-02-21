#include "CPacketMonsterData.h"

long long CPacketMonsterData::getUID()
{
   return m_uid;
}

int CPacketMonsterData::getKindID()
{
   return m_kindID;
}

void CPacketMonsterData::pack(CMonster *pMonster)
{
   m_uid            = pMonster->getUID();
   m_kindID         = pMonster->getID();
   m_advAttr        = pMonster->getAdvAttr();
   m_position       = pMonster->getPosition();
   m_targetPosition = pMonster->getTargetPosition();
   m_fDirection     = pMonster->getDirection();
   m_state          = pMonster->m_state;
   //m_bornPosition   = pMonster->m_bornPosition;
   //m_anchorPosition = pMonster->m_anchorPosition;
}

void CPacketMonsterData::unpack(CMonster *pMonster)
{
   pMonster->setUID(m_uid);
   pMonster->setAdvAttr(m_advAttr);
   pMonster->setPosition(m_position.fX, m_position.fY);
   pMonster->setTargetPosition(m_targetPosition.fX, m_targetPosition.fY);
   pMonster->setDirection(m_fDirection);
   pMonster->m_state = m_state;
   //pMonster->m_bornPosition = m_bornPosition;
   //pMonster->m_anchorPosition = m_anchorPosition;

   if(pMonster->isReachTarget() == false) {
      CActionEvent actEvent;
      actEvent.m_event = AET_NOT_REACH;
      CActionDispatch::getInstance()->sendEvnet(pMonster->getMachineName(), pMonster->getUID(), actEvent);
   }
}

#ifdef _GAMEENGINE_3D_
void CPacketMonsterData::unpack(CMonster3D *pMonster)
{
   this->unpack(pMonster->getMonster2D());
}
#endif