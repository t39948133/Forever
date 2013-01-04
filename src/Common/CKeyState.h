/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyState.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/13 */
#ifndef _CKEYSTATE_H_
#define _CKEYSTATE_H_
#include "Common.h"

class CKeyState
{
   public:
      CKeyState();

      /** @brief 設定要監測的按鍵
        * @param key 按鍵代碼 */
      void setKey(int key);

      /** @brief 回傳是否為按下的瞬間 */
      bool isPress();       

      /** @brief 回傳是否為壓著的瞬間 */
      bool isDown();

      /** @brief 按鍵狀態檢查 */
      void work();

   private:
      int  m_iKeyID;     // 監測的按鍵代碼
      bool m_bPrevDown;  // 上次按鍵是否壓著
      bool m_bPress;     // 按鍵是不是剛剛按下去的瞬間
      bool m_bDown;      // 按鍵是不是壓著
};

#endif  // #ifndef _CKEYSTATE_H_