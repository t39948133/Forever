/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IMouseEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/16 */
#ifndef _IMOUSEEVENTLISTENER_H_
#define _IMOUSEEVENTLISTENER_H_
#include "Common.h"
#include <OISMouse.h>

class IMouseEventListener
{
   public:
      /** @brief 滑鼠按鍵按下
        * @param evt 滑鼠相關資訊
        * @param id  那個滑鼠按鍵 */
      virtual void mouseDown(const OIS::MouseEvent &evt) = 0;

      /** @brief 滑鼠移動
        * @param evt 滑鼠相關資訊 */
      virtual void mouseMove(const OIS::MouseEvent &evt) = 0;

      /** @brief 滑鼠按鍵放開
        * @param evt 滑鼠相關資訊 
        * @param id  那個滑鼠按鍵 */
      virtual void mouseUp(const OIS::MouseEvent &evt) = 0;
};

#endif  // #ifndef _IMOUSEEVENTLISTENER_H_