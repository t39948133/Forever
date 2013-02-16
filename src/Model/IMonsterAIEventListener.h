/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IMonsterAIEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/12 */
#ifndef _IMONSTERAIEVENTLISTENER_H_
#define _IMONSTERAIEVENTLISTENER_H_
#include "Common.h"

class CMonster;

class IMonsterAIEventListener
{
   public:
      /** @brief 更新目標物 */
      virtual void updateMonsterTargetObject(CMonster *pMonster, long long newTargetObjectUID) = 0;

      /** @brief 更新怪物AI */
      virtual void updateMonsterAI(CMonster *pMonster) = 0;
};

#endif  // #ifndef _IMONSTERAIEVENTLISTENER_H_