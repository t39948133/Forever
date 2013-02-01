/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CCastSkillActionEvent.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CCASTSKILLACTIONEVENT_H_
#define _CCASTSKILLACTIONEVENT_H_
#include "CActionEvent.h"

// AET_CAST_SKILL專用，當施展技能時，動作系統會觸發而改變動作
class CCastSkillActionEvent : public CActionEvent
{
   public:
      CCastSkillActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      bool  m_bCastSkill;      // 是否施展技能
      int   m_iCastSkillID;    // 技能編號
      float m_fCastSkillTime;  // 施展時間
};

#endif  // #ifndef _CCASTSKILLACTIONEVENT_H_