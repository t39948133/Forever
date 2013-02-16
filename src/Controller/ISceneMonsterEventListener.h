/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   ISceneMonsterEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/16 */
#ifndef _ISCENEMONSTEREVENTLISTENER_H_
#define _ISCENEMONSTEREVENTLISTENER_H_
#include "Common.h"

class CMonster;

/** @brief 場景怪物事件監聽, 可以通知需要知道的物件 (用於Server端) */
class ISceneMonsterEventListener
{
   public:
      /** @brief 更新加怪物
        * @param pMonster 新加的怪物 */
      virtual void updateAddMonster(CMonster *pMonster) = 0;
};

#endif  // #ifndef _ISCENEMONSTEREVENTLISTENER_H_