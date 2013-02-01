/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CCastSkillActionEvent.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#include "CCastSkillActionEvent.h"

CCastSkillActionEvent::CCastSkillActionEvent()
{
   m_bCastSkill = false;
   m_iCastSkillID = -1;
   m_fCastSkillTime = 0.0f;
}

void CCastSkillActionEvent::operator=(CActionEvent &actEvent)
{
   CActionEvent::operator=(actEvent);

   CCastSkillActionEvent &srcCastSkillActionEvent = (CCastSkillActionEvent &)actEvent;
   m_bCastSkill = srcCastSkillActionEvent.m_bCastSkill;
   m_iCastSkillID = srcCastSkillActionEvent.m_iCastSkillID;
   m_fCastSkillTime = srcCastSkillActionEvent.m_fCastSkillTime;
}

bool CCastSkillActionEvent::operator==(CActionEvent &actEvent)
{
   bool bRetActionEvent = CActionEvent::operator ==(actEvent);
   bool bRetCastSkillActionEvent = false;

   CCastSkillActionEvent &srcCastSkillActionEvent = (CCastSkillActionEvent &)actEvent;
   if((m_bCastSkill == srcCastSkillActionEvent.m_bCastSkill) &&
      (m_iCastSkillID == srcCastSkillActionEvent.m_iCastSkillID) &&
      (m_fCastSkillTime == srcCastSkillActionEvent.m_fCastSkillTime))
      bRetCastSkillActionEvent = true;
   else
      bRetCastSkillActionEvent = false;
   
   if((bRetActionEvent == true) && (bRetCastSkillActionEvent == true))
      return true;
   else
      return false;
}

void CCastSkillActionEvent::clear()
{
   CActionEvent::clear();
   m_bCastSkill = false;
   m_iCastSkillID = -1;
   m_fCastSkillTime = 0.0f;
}