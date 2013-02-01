/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlaySoundNotifyActionEvent.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/31 */
#include "CPlaySoundNotifyActionEvent.h"

CPlaySoundNotifyActionEvent::CPlaySoundNotifyActionEvent() : CNotifyActionEvent()
{
   m_soundFile.clear();
}

void CPlaySoundNotifyActionEvent::operator=(CActionEvent &actEvent)
{
   CNotifyActionEvent::operator=(actEvent);

   CPlaySoundNotifyActionEvent &srcPlaySoundNotifyActionEvent = (CPlaySoundNotifyActionEvent &)actEvent;
   m_soundFile = srcPlaySoundNotifyActionEvent.m_soundFile;
}

bool CPlaySoundNotifyActionEvent::operator==(CActionEvent &actEvent)
{
   bool bRetNotifyActionEvent = CNotifyActionEvent::operator ==(actEvent);
   bool bRetPlaySoundNotifyActionEvent = false;

   CPlaySoundNotifyActionEvent &srcPlaySoundNotifyActionEvent = (CPlaySoundNotifyActionEvent &)actEvent;
   if(m_soundFile == srcPlaySoundNotifyActionEvent.m_soundFile)
      bRetPlaySoundNotifyActionEvent = true;
   else
      bRetPlaySoundNotifyActionEvent = false;
   
   if((bRetNotifyActionEvent == true) && (bRetPlaySoundNotifyActionEvent == true))
      return true;
   else
      return false;
}

void CPlaySoundNotifyActionEvent::clear()
{
   CNotifyActionEvent::clear();
   m_soundFile.clear();
}