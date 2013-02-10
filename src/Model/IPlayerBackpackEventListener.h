/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerBackpackEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IPLAYERBACKPACKEVENTLISTENER_H_
#define _IPLAYERBACKPACKEVENTLISTENER_H_
#include "Common.h"

class CBackpack;

/** @brief 玩家裝備事件監聽, 可以通知需要知道的物件 */
class IPlayerBackpackEventListener
{
   public:
      /** @brief 更新玩家背包
        * @param pPlayer 更新的物件 */
      virtual void updatePlayerBackpack(CBackpack *pBackpack) = 0;
};

#endif  // #ifndef _IPLAYERBACKPACKEVENTLISTENER_H_