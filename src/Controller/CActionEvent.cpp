/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEvent.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/27 */
#include "CActionEvent.h"

CActionEvent::CActionEvent()
{
   m_event      = AET_NULL;
   m_iKeyID     = 0;
   m_iKeyDownID = 0;
   m_iKeyUpID   = 0;
}

void CActionEvent::operator=(CActionEvent &actEvent)
{
   m_event      = actEvent.m_event;
   m_iKeyID     = actEvent.m_iKeyID;
   m_iKeyDownID = actEvent.m_iKeyDownID;
   m_iKeyUpID   = actEvent.m_iKeyUpID;
}

bool CActionEvent::operator==(CActionEvent &actEvent)
{
   bool bRet = false;

   if((actEvent.m_event  == m_event) &&
      (actEvent.m_iKeyID == m_iKeyID) &&
      (actEvent.m_iKeyDownID == m_iKeyDownID) &&
      (actEvent.m_iKeyUpID   == m_iKeyUpID))
      bRet = true;

   return bRet;
}

void CActionEvent::clear()
{
   m_event      = AET_NULL;
   m_iKeyID     = 0;
   m_iKeyDownID = 0;
   m_iKeyUpID   = 0;
}