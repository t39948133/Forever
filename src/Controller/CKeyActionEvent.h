/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyActionEvent.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CKEYACTIONEVENT_H_
#define _CKEYACTIONEVENT_H_
#include "CActionEvent.h"

// AET_KEY專用，當按下某按鍵時，動作系統會觸發而改變動作
class CKeyActionEvent : public CActionEvent
{
   public:
      CKeyActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      int m_iKeyID;  // 按鍵(使用Virtual key)
};

#endif  // #ifndef _CKEYACTIONEVENT_H_