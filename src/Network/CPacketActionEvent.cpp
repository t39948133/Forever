#include "CPacketActionEvent.h"
#include "CActionDispatch.h"

long long CPacketActionEvent::getUID()
{
   return m_uid;
}

void CPacketActionEvent::pack(CUnitObject *pUnitObject, CActionEvent *pActionEvent)
{
   m_uid = pUnitObject->getUID();
   m_event = pActionEvent->m_event;
}

void CPacketActionEvent::unpack(CUnitObject *pUnitObject)
{
   CActionEvent actEvent;
   actEvent.m_event = m_event;
   CActionDispatch::getInstance()->sendEvnet(pUnitObject->getMachineName(), pUnitObject->getUID(), actEvent);
}