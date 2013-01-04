/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IGameFlowListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#ifndef _IGAMEFLOWLISTENER_H_
#define _IGAMEFLOWLISTENER_H_
#include "Common.h"

/** @brief 遊戲流程訊息
  *        繼承此介面的物件可以收到繪圖引擎所發出的流程訊息 */
class IGameFlowListener
{
   public:
      /** @brief 建立場景 */
      virtual void createScene() = 0;

      /** @brief 開始繪圖之前的遊戲邏輯更新 */
      virtual bool frameRenderingQueued(float timeSinceLastFrame) = 0;

      /** @brief 釋放場景記憶體 */
      virtual void destoryScene() = 0;
};

#endif // #ifndef _IGAMEFLOWLISTENER_H_