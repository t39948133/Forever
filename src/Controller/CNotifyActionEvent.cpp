/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CNotifyActionEvent.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/29 */
#include "CNotifyActionEvent.h"

CNotifyActionEvent::CNotifyActionEvent()
{
   m_fBeginTime = -1.0f;
   m_fEndTime = -1.0f;
}

void CNotifyActionEvent::operator=(CActionEvent &actEvent)
{
   CActionEvent::operator=(actEvent);

   CNotifyActionEvent &srcNotifyActionEvent = (CNotifyActionEvent &)actEvent;
   m_fBeginTime = srcNotifyActionEvent.m_fBeginTime;
   m_fEndTime = srcNotifyActionEvent.m_fEndTime;
}

bool CNotifyActionEvent::operator==(CActionEvent &actEvent)
{
   bool bRetActionEvent = CActionEvent::operator ==(actEvent);
   bool bRetNotifyActionEvent = false;

   CNotifyActionEvent &srcNotifyActionEvent = (CNotifyActionEvent &)actEvent;
   if((m_fBeginTime == srcNotifyActionEvent.m_fBeginTime) &&
      (m_fEndTime == srcNotifyActionEvent.m_fEndTime))
      bRetNotifyActionEvent = true;
   else
      bRetNotifyActionEvent = false;
   
   if((bRetActionEvent == true) && (bRetNotifyActionEvent == true))
      return true;
   else
      return false;
}

void CNotifyActionEvent::clear()
{
   CActionEvent::clear();
   m_fBeginTime = -1.0f;
   m_fEndTime = -1.0f;
}