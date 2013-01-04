/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEventHandler.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#ifndef _CACTIONEVENTHANDLER_H_
#define _CACTIONEVENTHANDLER_H_
#include "Common.h"
#include "CActionEvent.h"

/** @brief 觸發動作改變的事件 */
class CActionEventHandler
{
   public:
      CActionEventHandler();
      ~CActionEventHandler();

      /** @brief 初始化
        * @param triggerEvent 觸發動作事件
        * @param nextActionID 下一個動作 */
      void init(CActionEvent &triggerEvent, int nextActionID);

      /** @brief 取得下一個動作編號
        * @return 動作編號 */
      int getNextActionID();

      /** @brief 檢查觸發的事件是否與Handler相符合
        * @param pEvent       觸發的動作事件
        * @param pKeyDownList 按鍵按下的列表
        * @return true - 相符合 / false - 不符合 */
      bool check(CActionEvent *pEvent, std::list<int> *pKeyDownList);

   private:
      CActionEvent m_triggerEvent;   // 觸發訊息
      int          m_iNextActionID;  // 觸發後要執行某個動作
};

#endif  // #ifndef _CACTIONEVENTHANDLER_H_