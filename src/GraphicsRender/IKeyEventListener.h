/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IKeyEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/16 */
#ifndef _IKEYEVENTLISTENER_H_
#define _IKEYEVENTLISTENER_H_
#include "Common.h"
#include <OISKeyboard.h>

class IKeyEventListener
{
   public:
      /** @brief 鍵盤按鍵按下
        * @param evt 鍵盤相關資訊 */
      virtual void keyDown(const OIS::KeyEvent &evt) = 0;

      /** @brief 鍵盤按鍵放開
        * @param evt 鍵盤相關資訊 */
      virtual void keyUp(const OIS::KeyEvent &evt) = 0;
};

#endif  // #ifndef _IKEYEVENTLISTENER_H_