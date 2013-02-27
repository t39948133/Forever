/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IFightEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/20 */
#ifndef _IFIGHTEVENTLISTENER_H_
#define _IFIGHTEVENTLISTENER_H_
#include "Common.h"

class CActionEvent;
class CCastSkillActionEvent;

/** @brief 戰鬥系統事件監聽, 可以通知需要知道的物件 (用於Server端) */
class IFightEventListener
{
   public:
      /** @brief 更新戰鬥系統發出的動作訊息 
        * @param pUnitObject 誰
        * @param pActEvent   動作訊息 */
      virtual void updateFightActionEvent(CUnitObject *pUnitObject, CActionEvent *pActEvent) = 0;

      /** @brief 更新使用技能之前要跑步到目標物
        * @param pUnitObject   誰 */
      virtual void updateFightTargetPosition(CUnitObject *pUnitObject) = 0;

      /** @brief 更新目標物死亡後的處理
        * @param pUnitObject   誰
        * @param pTargetObject 目標物 */
      virtual void updateFightTargetDead(CUnitObject *pUnitObject, CUnitObject *pTargetObject) = 0;
};

#endif  // #ifndef _IFIGHTEVENTLISTENER_H_