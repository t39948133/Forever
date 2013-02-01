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
}

void CActionEvent::operator=(CActionEvent &actEvent)
{
   m_event      = actEvent.m_event;
}

bool CActionEvent::operator==(CActionEvent &actEvent)
{
   if(actEvent.m_event == m_event)
      return true;
   else
      return false;
}

void CActionEvent::clear()
{
   m_event      = AET_NULL;
}