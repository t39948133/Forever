/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyMan.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/13 */
#ifndef _CKEYMAN_H_
#define _CKEYMAN_H_
#include "CKeyState.h"

typedef enum tagVIRTUAL_KEY {
   KEY_W, KEY_A, KEY_S, KEY_D,  // 鍵盤移動
   KEY_LBUTTON, KEY_RBUTTON,    // 滑鼠左右鍵
   KEY_P,                       // 人物資訊視窗
   KEY_B,                       // 背包視窗
   KEY_K,                       // 技能視窗
   KEY_COUNT
} VIRTUAL_KEY;

class CKeyMan
{
   public:
      CKeyMan();

      bool isPress(VIRTUAL_KEY key);
      bool isDown(VIRTUAL_KEY key);
      bool isUp(VIRTUAL_KEY key);
      void work();

   private:
      CKeyState m_keyState[KEY_COUNT];
};

#endif  // #ifndef _CKEYMAN_H_