/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindowMan3D.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/09 */
#ifndef _CWINDOWMAN3D_H_
#define _CWINDOWMAN3D_H_
#ifdef _GAMEENGINE_3D_
#include "CWindowMan.h"
#include "IKeyEventListener.h"
#include "IMouseEventListener.h"

class CWindowMan3D : public CWindowMan,
                     public IKeyEventListener,
                     public IMouseEventListener
{
   public:
      CWindowMan3D();
      virtual ~CWindowMan3D();

      // CWindowMan
      /* virtual */ void addWnd(CWindow *pWnd);

      // IKeyEventListener
      /* virtual */ void keyDown(const OIS::KeyEvent &evt);
      /* virtual */ void keyUp(const OIS::KeyEvent &evt);

      // IMouseEventListener
      /* virtual */ void mouseDown(const OIS::MouseEvent &evt);
      /* virtual */ void mouseMove(const OIS::MouseEvent &evt);
      /* virtual */ void mouseUp(const OIS::MouseEvent &evt);

      bool isPressWindow(int x, int y);  // 滑鼠左鍵是否有按到視窗
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CWINDOWMAN3D_H_