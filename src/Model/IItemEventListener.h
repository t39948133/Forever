/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IItemEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/21 */
#ifndef _IITEMEVENTLISTENER_H_
#define _IITEMEVENTLISTENER_H_
#include "Common.h"

class CItem;

/** @brief 物品欄事件監聽, 可以通知需要知道的物件 */
class IItemEventListener
{
   public:
      /** @brief 更新物品欄資料
        * @param pItem 更新的物品欄 */
      virtual void updateItemData(CItem *pItem) = 0;
};

#endif  // #ifndef _IITEMEVENTLISTENER_H_