/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWASDKeyActionEvent.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#include "CWASDKeyActionEvent.h"

CWASDKeyActionEvent::CWASDKeyActionEvent()
{
   m_iKeyDownID = 0;
   m_iKeyUpID = 0;
}

void CWASDKeyActionEvent::operator=(CActionEvent &actEvent)
{
   CActionEvent::operator=(actEvent);

   CWASDKeyActionEvent &srcWASDKeyActionEvent = (CWASDKeyActionEvent &)actEvent;
   m_iKeyDownID = srcWASDKeyActionEvent.m_iKeyDownID;
   m_iKeyUpID = srcWASDKeyActionEvent.m_iKeyUpID;
}

bool CWASDKeyActionEvent::operator==(CActionEvent &actEvent)
{
   bool bRetActionEvent = CActionEvent::operator ==(actEvent);
   bool bRetWASDKeyActionEvent = false;

   CWASDKeyActionEvent &srcWASDKeyActionEvent = (CWASDKeyActionEvent &)actEvent;
   if((m_iKeyDownID == srcWASDKeyActionEvent.m_iKeyDownID) &&
      (m_iKeyUpID == srcWASDKeyActionEvent.m_iKeyUpID))
      bRetWASDKeyActionEvent = true;
   else
      bRetWASDKeyActionEvent = false;
   
   if((bRetActionEvent == true) && (bRetWASDKeyActionEvent == true))
      return true;
   else
      return false;
}

void CWASDKeyActionEvent::clear()
{
   CActionEvent::clear();
   m_iKeyDownID = 0;
   m_iKeyUpID = 0;
}