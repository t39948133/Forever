/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IDeadEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/21 */
#ifndef _IDEADEVENTLISTENER_H_
#define _IDEADEVENTLISTENER_H_
#include "Common.h"

class CUnitObject;

/** @brief 怪物/NPC/玩家死亡事件監聽, 可以通知需要知道的物件 */
class IDeadEventListener
{
   public:
      /** @brief 更新有某物件死亡 
        * @param uid 誰 */
      virtual void updateDead(long long uid) = 0;
};

#endif  // #ifndef _IDEADEVENTLISTENER_H_