/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEvent.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/27 */
#ifndef _CACTIONEVENT_H_
#define _CACTIONEVENT_H_
#include "Common.h"

/** @brief 動作事件 */
class CActionEvent
{
   public:
      CActionEvent();

      /** @brief 物件拷貝
        * @param actEvent CActionEvent物件 */
      void operator=(CActionEvent &actEvent);

      /** @brief 物件判斷
        * @param actEvent CActionEvent物件 */
      bool operator==(CActionEvent &actEvent);

      /** @brief 清除資料 */
      void clear();

      ACTION_EVENT_TYPE m_event;       // 動作事件

      // AET_KEY (單一按鍵)
      int               m_iKeyID;      // 按鍵(使用Virtual key)

      // AET_KEY_COMBIN (多個按鍵)
      int               m_iKeyDownID;  // 按下按鍵(使用Virtual key)
      int               m_iKeyUpID;    // 放開按鍵(使用Virtual key)

      // AET_CAST_SKILL (技能施展)
      bool              m_bCastSkill;      // 是否施展技能
      unsigned int      m_iCastSkillID;    // 技能編號
      float             m_fCastSkillTime;  // 施展時間

      // AET_CALLBACK_XXXX  (動作系統會依據此訊息來發出訊息給外部)
      //float             m_fBeginTime;      // 該事件的開始觸發時間
      //float             m_fEndTime;        // 該事件的結束觸發時間
};

#endif  // #ifndef _CACTIONEVENT_H_