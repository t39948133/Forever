/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyActionEvent.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#include "CKeyActionEvent.h"

CKeyActionEvent::CKeyActionEvent()
{
   m_iKeyID = 0;
}

void CKeyActionEvent::operator=(CActionEvent &actEvent)
{
   CActionEvent::operator=(actEvent);

   CKeyActionEvent &srcKeyActionEvent = (CKeyActionEvent &)actEvent;
   m_iKeyID = srcKeyActionEvent.m_iKeyID;
}

bool CKeyActionEvent::operator==(CActionEvent &actEvent)
{
   bool bRetActionEvent = CActionEvent::operator ==(actEvent);
   bool bRetKeyActionEvent = false;

   CKeyActionEvent &srcKeyActionEvent = (CKeyActionEvent &)actEvent;
   if(m_iKeyID == srcKeyActionEvent.m_iKeyID)
      bRetKeyActionEvent = true;
   else
      bRetKeyActionEvent = false;
   
   if((bRetActionEvent == true) && (bRetKeyActionEvent == true))
      return true;
   else
      return false;
}

void CKeyActionEvent::clear()
{
   CActionEvent::clear();
   m_iKeyID = 0;
}