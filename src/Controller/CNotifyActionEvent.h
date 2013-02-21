/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CNotifyActionEvent.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/29 */
#ifndef _CNOTIFYACTIONEVENT_H_
#define _CNOTIFYACTIONEVENT_H_
#include "CActionEvent.h"

/** @brief 動作系統通知外部物件的訊息
  *        動作系統會依據某個時間點而通知外部某訊息
  *        給沒有參數的事件使用
  *        Ex: AET_NOTIFY_DRAW_WEAPON,
  *            AET_NOTIFY_PUTIN_WEAPON,
  *            AET_NOTIFY_ATTACK */
class CNotifyActionEvent : public CActionEvent
{
   public:
      CNotifyActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      float m_fBeginTime;      // 此事件的開始觸發時間
      float m_fEndTime;        // 此事件的結束觸發時間
};

#endif  // #ifndef _CNOTIFYACTIONEVENT_H_