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

/** @brief 動作事件
  *        給事件沒有參數的使用 
  *        ex: AET_REACH, AET_NOT_REACH */
class CActionEvent
{
   public:
      CActionEvent();

      /** @brief 物件拷貝
        * @param actEvent CActionEvent物件 */
      virtual void operator=(CActionEvent &actEvent);

      /** @brief 物件判斷
        * @param actEvent CActionEvent物件 */
      virtual bool operator==(CActionEvent &actEvent);

      /** @brief 清除資料 */
      virtual void clear();

      ACTION_EVENT_TYPE m_event;       // 動作事件
};

#endif  // #ifndef _CACTIONEVENT_H_