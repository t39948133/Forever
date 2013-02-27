/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CLoadingWnd.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/22 */
#ifndef _CLOADINGWND_H_
#define _CLOADINGWND_H_
#ifdef _GAMEENGINE_3D_
#include "CWindow.h"
#include "COverlayUI.h"

class CLoadingWnd : public CWindow
{
   public:
      CLoadingWnd();

      void init(int _x, int _y, int width, int height);

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);
      /* virtual */ int getZOrder();

   private:
      COverlayUI  m_overlay;  //ºÞ²zoverlay
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CLOADINGWND_H_