/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerHotKeyEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/21 */
#ifndef _IPLAYERHOTKEYEVENTLISTENER_H_
#define _IPLAYERHOTKEYEVENTLISTENER_H_
#include "Common.h"

typedef struct tagHOTKEYITEM HotKeyItem;

/** @brief 快捷鍵事件監聽, 可以通知需要知道的物件 */
class IPlayerHotKeyEventListener
{
   public:
      /** @brief 更新玩家的快捷鍵
        * @param pHotKeyItem 更新的快捷鍵 */
      virtual void updatePlayerHotKey(HotKeyItem *pHotKeyItem) = 0;
};

#endif  // #ifndef _IPLAYERHOTKEYEVENTLISTENER_H_