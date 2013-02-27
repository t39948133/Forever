/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerAttrEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IPLAYERATTREVENTLISTENER_H_
#define _IPLAYERATTREVENTLISTENER_H_
#include "Common.h"

class CPlayer;

/** @brief 玩家屬性事件監聽, 可以通知需要知道的物件 */
class IPlayerAttrEventListener
{
   public:
      /** @brief 更新玩家屬性 (XP, Money變動時)
        * @param pPlayer 更新的物件 */
      virtual void updatePlayerAttr(CPlayer *pPlayer, unsigned int offsetXP, long long offsetMoney) = 0;
};

#endif  // #ifndef _IPLAYERATTREVENTLISTENER_H_