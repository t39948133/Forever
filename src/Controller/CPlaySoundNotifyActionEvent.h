/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlaySoundNotifyActionEvent.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/31 */
#ifndef _CPLAYSOUNDNOTIFYACTIONEVENT_H_
#define _CPLAYSOUNDNOTIFYACTIONEVENT_H_
#include "CNotifyActionEvent.h"

/** @brief 發出動作音效通知 */
class CPlaySoundNotifyActionEvent : public CNotifyActionEvent
{
   public:
      CPlaySoundNotifyActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      std::string m_soundFile;  // 音效檔名
};

#endif  // #ifndef _CPLAYSOUNDNOTIFYACTIONEVENT_H_