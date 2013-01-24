/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IAdvAttrEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IADVATTREVENTLISTENER_H_
#define _IADVATTREVENTLISTENER_H_
#include "Common.h"

class CUnitObject;

/** @brief AdvancedAttribute(進階屬性)事件監聽, 可以通知需要知道的物件 */
class IAdvAttrEventListener
{
   public:
      /** @brief 更新進階屬性 
        * @param pUnitObject 更新的物件 */
      virtual void updateAdvAttr(CUnitObject *pUnitObject) = 0;
};

#endif  // #ifndef _IADVATTREVENTLISTENER_H_