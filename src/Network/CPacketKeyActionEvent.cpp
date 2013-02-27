#include "CPacketKeyActionEvent.h"
#include "CActionDispatch.h"

long long CPacketKeyActionEvent::getUID()
{
   return m_uid;
}

void CPacketKeyActionEvent::pack(CUnitObject *pUnitObject, CKeyActionEvent *pActionEvent)
{
   m_uid = pUnitObject->getUID();
   m_event = pActionEvent->m_event;
   m_iKeyID = pActionEvent->m_iKeyID;
}

void CPacketKeyActionEvent::unpack(CUnitObject *pUnitObject)
{
   CKeyActionEvent actEvent;
   actEvent.m_event = m_event;
   actEvent.m_iKeyID = m_iKeyID;
   CActionDispatch::getInstance()->sendEvnet(pUnitObject->getMachineName(), pUnitObject->getUID(), actEvent);
}