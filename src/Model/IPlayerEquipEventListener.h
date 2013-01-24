/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerEquipEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IPLAYEREQUIPEVENTLISTENER_H_
#define _IPLAYEREQUIPEVENTLISTENER_H_
#include "Common.h"

class CPlayer;

/** @brief 玩家裝備事件監聽, 可以通知需要知道的物件 */
class IPlayerEquipEventListener
{
   public:
      /** @brief 更新玩家裝備
        * @param pPlayer 更新的物件 */
      virtual void updatePlayerEquip(CPlayer *pPlayer) = 0;
};

#endif  // #ifndef _IPLAYEREQUIPEVENTLISTENER_H_