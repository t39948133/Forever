/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWASDKeyActionEvent.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CWASDKEYACTIONEVENT_H_
#define _CWASDKEYACTIONEVENT_H_
#include "CActionEvent.h"

// AET_KEY_WASD專用，當按下/放開某按鍵時，動作系統會觸發而改變動作
class CWASDKeyActionEvent : public CActionEvent
{
   public:
      CWASDKeyActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      int m_iKeyDownID;  // 按下按鍵(使用Virtual key)
      int m_iKeyUpID;    // 放開按鍵(使用Virtual key)
};

#endif  // #ifndef _CWASDKEYACTIONEVENT_H_