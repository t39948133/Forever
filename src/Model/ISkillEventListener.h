/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   ISkillEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/21 */
#ifndef _ISKILLEVENTLISTENER_H_
#define _ISKILLEVENTLISTENER_H_
#include "Common.h"

class CUnitObject;
class CSkill;

/** @brief 技能事件監聽, 可以通知需要知道的物件 */
class ISkillEventListener
{
   public:
      /** @brief 更新作戰單位技能
        * @param pUnitObject 更新的物件 */
      virtual void updateSkill(CUnitObject *pUnitObject) = 0;

      /** @brief 更新技能冷卻時間
        * @param pSkill 技能 */
      virtual void updateSkillCoolDown(CSkill *pSkill) = 0;
};

#endif  // #ifndef _ISKILLEVENTLISTENER_H_