/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionDispatch.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/22 */
#ifndef _CACTIONDISPATCH_H_
#define _CACTIONDISPATCH_H_
#include "Common.h"
#include "CActionSystem.h"

/** @brief 動作訊息派送 */
class CActionDispatch
{
   public:
      /** @brief 取得CActionDispatch實體物件
        * @return CActionDispatch實體物件 */
      static CActionDispatch* getInstance();

      /** @brief 釋放CActionDispatch實體物件 */
      static void releaseInstance();

      /** @brief 加入要收到動作訊息的動作系統物件
        * @param uid           CUnitObject的uid
        * @param pActionSystem 動作系統物件 */
      void addActionSystem(long long uid, CActionSystem *pActionSystem);

      /** @brief 送給某個uid動作訊息
        * @param uid      CUnitObject的uid
        * @param actEvent 動作訊息 */
      void sendEvnet(long long uid, CActionEvent &actEvent);

   private:
      CActionDispatch();
      ~CActionDispatch();

      static CActionDispatch *m_pInstance;  // CActionDispatch實體物件

      std::map<long long, CActionSystem*> *m_pEventTable;  // 訊息對照表
};

#endif  // #ifndef _CACTIONDISPATCH_H_